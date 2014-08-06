// This small C++11 file can be compiled with various options. For example,
// "CXX -std=c++11 -D_EXPOSE_BUG_ generic_hw_sw_benchmark.cpp" produces an
// executable file that when run exposes the concurrency bug.

#include <cassert>
#include <thread>
#include <mutex>

char symbolic_char(char c)
{
  return c;
}

// There are three ways to expose the concurrency bug:
// 1) delay enabling of interrupt so that an intermittent
//    stimulus won't trigger an interrupt;
// 2) delay the firing of the interrupt handler until
//    after the verification condition check;
// 3) generate stimulus before polling starts.
#ifdef _EXPOSE_BUG_
#include <chrono>

constexpr std::chrono::seconds SHORT_DELAY(1);
constexpr std::chrono::seconds LONG_DELAY(3);
#endif

// Marginally useful in case of concurrent outputs
#ifdef _ENABLE_OUTPUT_
#include <iostream>
#endif

// ========= Hardware model =========

typedef char Register;
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
  std::mutex& mutex_ref;

public:
  AutomaticMutex(std::mutex& mutex)
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

  std::mutex mutex;

  Register regs[REG_NR];
  bool is_on;

  // Fire interrupt whenever handler is not null
  InterruptHandler interrupt_handler;
};

// By default interrupts are disabled
void turn_on(struct Hardware *hw)
{
  AutomaticMutex automatic_mutex(hw->mutex);

#ifdef _ENABLE_OUTPUT_
  std::cout << "Turn on hardware" << std::endl;
#endif

  for (unsigned reg_id = 0; reg_id < REG_NR; ++reg_id)
    hw->regs[reg_id] = ZERO_BYTE;

  hw->is_on = true;
  hw->interrupt_handler = nullptr;
}

void turn_off(struct Hardware *hw)
{
  AutomaticMutex automatic_mutex(hw->mutex);

#ifdef _ENABLE_OUTPUT_
  std::cout << "Turn off hardware" << std::endl;
#endif

  hw->is_on = false;
}

// Does not write any registers but sets function pointer
void enable_interrupts(struct Hardware *hw, InterruptHandler interrupt_handler)
{
  AutomaticMutex automatic_mutex(hw->mutex);
  hw->interrupt_handler = interrupt_handler;
}

// Read control register
Register read_signal_register(struct Hardware *hw)
{
  AutomaticMutex automatic_mutex(hw->mutex);

  if (!hw->is_on)
  {
#ifdef _ENABLE_OUTPUT_
    std::cout << "Read signal [off]" << std::endl;
#endif
    return ZERO_BYTE;
  }

  return hw->regs[SIGNAL_REG_ID];
}

// Internal check that `reg_id' refers to a data register
void check_data_register(RegisterId reg_id)
{
  assert(0 < reg_id && reg_id < REG_NR);
}

// Read data from hardware register
Register read_data_register(struct Hardware *hw, RegisterId reg_id)
{
  AutomaticMutex automatic_mutex(hw->mutex);
  check_data_register(reg_id);

  if (!hw->is_on)
  {
#ifdef _ENABLE_OUTPUT_
    std::cout << "Read register [off] " << reg_id << std::endl;
#endif
    return ZERO_BYTE;
  }

  Register value = hw->regs[reg_id];
  hw->regs[SIGNAL_REG_ID] &= ~reg_id;

#ifdef _ENABLE_OUTPUT_
  std::cout << "Read register [on] reg_id: " << reg_id << " value: " << value << std::endl;
#endif

  return value;
}

// Write data to hardware register
void write_data_register(struct Hardware *hw, RegisterId reg_id, Register value)
{
  AutomaticMutex automatic_mutex(hw->mutex);
  check_data_register(reg_id);

  if (!hw->is_on)
  {
#ifdef _ENABLE_OUTPUT_
    std::cout << "Write register [off] reg_id: " << reg_id << " value: " << value << std::endl;
#endif
    return;
  }

#ifdef _ENABLE_OUTPUT_
  std::cout << "Write register [on] reg_id: " << reg_id << " value: " << value << std::endl;
#endif

  hw->regs[reg_id] = value;
  hw->regs[SIGNAL_REG_ID] |= reg_id;

  if (hw->interrupt_handler)
  {
#ifdef _ENABLE_OUTPUT_
    std::cout << "Fire interrupt" << std::endl;
#endif

#ifdef _EXPOSE_BUG_
    // delay firing of interrupt
    std::this_thread::sleep_for(LONG_DELAY);
#endif

    std::thread interrupt_thread(hw->interrupt_handler, hw->fw);
  }
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
#ifdef _ENABLE_OUTPUT_
  std::cout << "Handle interrupt" << std::endl;
#endif

  read_data_register(fw->hw, DATA_A_REG_ID);
}

// Firmware's main function

// Switches from polling to interrupt mode if
// there is no newly written data to read.
void poll(struct Firmware *fw)
{
  char byte = read_signal_register(fw->hw);

  if (byte == ZERO_BYTE)
  {
#ifdef _ENABLE_OUTPUT_
    std::cout << "Switch from polling to interrupt mode" << std::endl;
#endif

    enable_interrupts(fw->hw, handle_interrupt);
  }
  else
  {
#ifdef _ENABLE_OUTPUT_
    std::cout << "Stay in polling mode and read hardware register" << std::endl;
#endif

    read_data_register(fw->hw, DATA_A_REG_ID);
  }
}

// ========= Test harness =========

void stimulus(struct Hardware *hw)
{
  Register value = symbolic_char('A');

#ifdef _ENABLE_OUTPUT_
  std::cout << "Generate stimulus" << std::endl;
#endif

  write_data_register(hw, DATA_A_REG_ID, value);
}

int main()
{
#ifdef _ENABLE_OUTPUT_
  std::cout << "C++ main() function" << std::endl;
#endif

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
  std::thread firmware_thread(poll, fw);

#ifdef _EXPOSE_BUG_
  std::this_thread::sleep_for(SHORT_DELAY);
#endif

  // environment stimulus
  std::thread stimulus_thread(stimulus, hw);

#ifdef _EXPOSE_BUG_
  std::this_thread::sleep_for(SHORT_DELAY);
#endif

  // stop hardware
  turn_off(hw);

  // check verification condition:
  //
  // the firmware must have reacted to every environment
  // stimulus that triggered the hardware functionality.
  assert(hardware.regs[SIGNAL_REG_ID] == 0);

  firmware_thread.join();
  stimulus_thread.join();

  return 0;
}
