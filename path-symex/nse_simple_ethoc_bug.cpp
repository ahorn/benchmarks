#include <crv.h>

#define CHECK(condition) crv::dfs_checker().add_error(!(condition));

// ========= Hardware model =========

typedef int Register;
constexpr Register ZERO_BYTE = '\0';

enum RegisterId
{
  SIGNAL_REG_ID = 0,
  DATA_A_REG_ID = 1,

  REG_NR = 2
};

typedef enum RegisterId RegisterId;

// Utility class for RAII on locks
class AutomaticMutex
{
private:
  crv::Mutex& mutex_ref;

public:
  AutomaticMutex(crv::Mutex& mutex)
  : mutex_ref(mutex)
  {
    mutex_ref.lock();
  }

  ~AutomaticMutex()
  {
    mutex_ref.unlock();
  }
};

struct Firmware;
typedef void (*InterruptHandler)(struct Firmware*);

struct Hardware
{
  struct Firmware* fw;

  crv::Mutex mutex;

  crv::External<Register[REG_NR]> regs;
  crv::External<bool> is_on;

  // Fire interrupt whenever handler is not null
  InterruptHandler interrupt_handler;
};

// By default interrupts are disabled
void turn_on(struct Hardware *hw)
{
  AutomaticMutex automatic_mutex(hw->mutex);

  for (unsigned reg_id = 0; reg_id < REG_NR; ++reg_id)
    hw->regs[reg_id] = ZERO_BYTE;

  hw->is_on = true;
  hw->interrupt_handler = nullptr;
}

void turn_off(struct Hardware *hw)
{
  AutomaticMutex automatic_mutex(hw->mutex);
  hw->is_on = false;
}

// Does not write any registers but sets function pointer
void enable_interrupts(struct Hardware *hw, InterruptHandler interrupt_handler)
{
  AutomaticMutex automatic_mutex(hw->mutex);
  hw->interrupt_handler = interrupt_handler;
}

// Read control register
crv::Internal<Register> read_signal_register(struct Hardware *hw)
{
  AutomaticMutex automatic_mutex(hw->mutex);

  if (crv::dfs_checker().branch(!hw->is_on))
    return ZERO_BYTE;

  return hw->regs[SIGNAL_REG_ID];
}

// Internal check that `reg_id' refers to a data register
void check_data_register(RegisterId reg_id)
{
  CHECK(0 < reg_id && reg_id < REG_NR);
}

// Read data from hardware register
crv::Internal<Register> read_data_register(struct Hardware *hw, RegisterId reg_id)
{
  AutomaticMutex automatic_mutex(hw->mutex);
  check_data_register(reg_id);

  if (crv::dfs_checker().branch(!hw->is_on))
    return ZERO_BYTE;

  crv::Internal<Register> value = hw->regs[reg_id];
  crv::Internal<Register> new_signal = hw->regs[SIGNAL_REG_ID] & static_cast<Register>(~reg_id);
  hw->regs[SIGNAL_REG_ID] = new_signal;

  return value;
}

// Write data to hardware register
void write_data_register(struct Hardware *hw, RegisterId reg_id, crv::Internal<Register> value)
{
  AutomaticMutex automatic_mutex(hw->mutex);
  check_data_register(reg_id);

  if (crv::dfs_checker().branch(!hw->is_on))
    return;

  hw->regs[reg_id] = value;
  crv::Internal<Register> new_signal = hw->regs[SIGNAL_REG_ID] | static_cast<Register>(reg_id);
  hw->regs[SIGNAL_REG_ID] = new_signal;

  if (hw->interrupt_handler)
    crv::Thread interrupt_thread(hw->interrupt_handler, hw->fw);
}

// ========= Firmware =========

// Reads the data registers
//
// Switches to interrupt mode if there
// is no data to read.
struct Firmware
{
  struct Hardware* hw;
};

// Interrupt handler for incoming data
void handle_interrupt(struct Firmware *fw)
{
  read_data_register(fw->hw, DATA_A_REG_ID);
}

// Firmware's main function

// Switches from polling to interrupt mode if
// there is no newly written data to read.
void poll(struct Firmware *fw)
{
  crv::Internal<Register> byte = read_signal_register(fw->hw);

  if (crv::dfs_checker().branch(byte == ZERO_BYTE))
    enable_interrupts(fw->hw, handle_interrupt);
  else
    read_data_register(fw->hw, DATA_A_REG_ID);
}

// ========= Test harness =========

void stimulus(struct Hardware *hw)
{
  crv::Internal<Register> value = crv::any<Register>();
  write_data_register(hw, DATA_A_REG_ID, value);
}

void nse_main()
{
  struct Hardware hardware;
  struct Hardware* hw = &hardware;

  struct Firmware firmware;
  struct Firmware* fw = &firmware;

  // burn firmware on chip
  firmware.hw = hw;
  hardware.fw = fw;

  // start hardware
  turn_on(hw);

  // start firmware
  crv::Thread firmware_thread(poll, fw);

  // environment stimulus
  crv::Thread stimulus_thread(stimulus, hw);

  // stop hardware
  turn_off(hw);

  // check verification condition:
  //
  // the firmware must have reacted to every environment
  // stimulus that triggered the hardware functionality.
  CHECK(hardware.regs[SIGNAL_REG_ID] == 0);

  firmware_thread.join();
  stimulus_thread.join();
}

int main()
{
  crv::Encoder encoder;
  bool error = false;

  do
  {
    nse_main();

    error = !crv::dfs_checker().errors().empty() &&
      smt::sat == encoder.check(crv::tracer(), crv::dfs_checker());
  }
  while (crv::dfs_checker().find_next_path() && !error);

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  return error;
}
