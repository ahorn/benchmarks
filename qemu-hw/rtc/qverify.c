#include "qverify.h"
#include "qemu-timer.h"
#include "mc146818rtc.h"

static QTestState _global_qverify;
QTestState *global_qverify;

void set_global_qverify_rtc_state(void* rtc_state) {
  global_qverify->rtc_state = rtc_state;
}

QTestState *qverify_init()
{
    return &_global_qverify;
}

int64_t qverify_clock_step_next(QTestState *s)
{
    return qemu_clock_deadline(vm_clock);
}

static void qverify_clock_warp(int64_t dest)
{
    int64_t clock = qemu_get_clock_ns(vm_clock);
    while (clock < dest) {
        qemu_run_timers(vm_clock);
        clock = qemu_get_clock_ns(vm_clock);
    }
}

int64_t qverify_clock_step(QTestState *s, int64_t step)
{
   qverify_clock_warp(qemu_get_clock_ns(vm_clock) + step);
   return qemu_get_clock_ns(vm_clock);
}

int64_t qverify_clock_set(QTestState *s, int64_t ns)
{
    qverify_clock_warp(ns);
    return qemu_get_clock_ns(vm_clock);
}

void qverify_outb(QTestState *s, uint16_t addr, uint8_t value)
{
    cmos_ioport_write(s->rtc_state, addr, value);
}

uint8_t qverify_inb(QTestState *s, uint16_t addr)
{
    return cmos_ioport_read(s->rtc_state, addr);
}

