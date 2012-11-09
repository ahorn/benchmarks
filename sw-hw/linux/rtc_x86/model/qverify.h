#ifndef QVERIFY_H
#define QVERIFY_H

#if ! (defined (_SYS_) || defined (_CBMC_))
    #include <stdint.h>
#endif

typedef struct QTestState QTestState;
struct QTestState
{
    void *rtc_state;
};

extern QTestState *global_qverify;

void set_global_qverify_rtc_state(void* rtc_state);

/**
 * qverify_init:
 *
 * Returns pointer to global QTestState.
 */
QTestState *qverify_init();

/**
 * qverify_outb:
 * @s: QTestState instance to operate on.
 * @addr: I/O port to write to.
 * @value: Value being written.
 *
 * Write an 8-bit value to an I/O port.
 */
void qverify_outb(QTestState *s, uint16_t addr, uint8_t value);

/**
 * qverify_inb:
 * @s: QTestState instance to operate on.
 * @addr: I/O port to read from.
 * @value: Value being written.
 *
 * Returns an 8-bit value from an I/O port.
 */
uint8_t qverify_inb(QTestState *s, uint16_t addr);

/**
 * qverify_clock_step_next:
 * @s: QTestState instance to operate on.
 *
 * Advance the vm_clock to the next deadline.  Return the current
 * value of the vm_clock in nanoseconds.
 */
int64_t qverify_clock_step_next(QTestState *s);

/**
 * qverify_clock_step:
 * @s: QTestState instance to operate on.
 * @step: Number of nanoseconds to advance the clock by.
 *
 * Advance the vm_clock by @step nanoseconds.  Return the current
 * value of the vm_clock in nanoseconds.
 */
int64_t qverify_clock_step(QTestState *s, int64_t step);

/**
 * qverify_clock_set:
 * @s: QTestState instance to operate on.
 * @val: Nanoseconds value to advance the clock to.
 *
 * Advance the vm_clock to @val nanoseconds since the VM was launched.
 * Return the current value of the vm_clock in nanoseconds.
 */
int64_t qverify_clock_set(QTestState *s, int64_t val);

/**
 * qverify_start:
 *
 * Start QEMU and assign the resulting QTestState to a global variable.
 * The global variable is used by "shortcut" macros documented below.
 */
#define qverify_start() (global_qverify = qverify_init())

/**
 * outb:
 * @addr: I/O port to write to.
 * @value: Value being written.
 *
 * Write an 8-bit value to an I/O port.
 */
#define outb(addr, val) qverify_outb(global_qverify, addr, val)

/**
 * inb:
 * @addr: I/O port to read from.
 * @value: Value being written.
 *
 * Returns an 8-bit value from an I/O port.
 */
#define inb(addr) qverify_inb(global_qverify, addr)

/**
 * clock_step_next:
 *
 * Advance the vm_clock to the next deadline.  Return the current
 * value of the vm_clock in nanoseconds.
 */
#define clock_step_next() qverify_clock_step_next(global_qverify)

/**
 * clock_step:
 * @step: Number of nanoseconds to advance the clock by.
 *
 * Advance the vm_clock by @step nanoseconds.  Return the current
 * value of the vm_clock in nanoseconds.
 */
#define clock_step(step) qverify_clock_step(global_qverify, step)

/**
 * clock_set:
 * @val: Nanoseconds value to advance the clock to.
 *
 * Advance the vm_clock to @val nanoseconds since the VM was launched.
 * Return the current value of the vm_clock in nanoseconds.
 */
#define clock_set(val) qverify_clock_set(global_qverify, val)

#endif
