#include "qemu-timer.h"
#include "mc146818rtc.h"
#include "qverify.h"

#include <stdint.h>

/* PC cmos mappings */

#define REG_EQUIPMENT_BYTE          0x14

typedef uint64_t ram_addr_t;

QEMUClock *rtc_clock;

/* use non-determinstic values */
ram_addr_t ram_size = 0;
int smp_cpus = 1;
int use_rt_clock = 0;

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

// See also pc_cmos_init() in pc.c
static void pc_cmos_init_for_rtc(RTCState *s)
{
    int val, nb;

    ram_addr_t above_4g_mem_size = 0;

    /* various important CMOS locations needed by PC/Bochs bios */

    /* memory size */
    /* base memory (first MiB) */
    val = MIN(ram_size / 1024, 640);
    rtc_set_memory(s, 0x15, val);
    rtc_set_memory(s, 0x16, val >> 8);
    /* extended memory (next 64MiB) */
    if (ram_size > 1024 * 1024) {
        val = (ram_size - 1024 * 1024) / 1024;
    } else {
        val = 0;
    }
    if (val > 65535)
        val = 65535;
    rtc_set_memory(s, 0x17, val);
    rtc_set_memory(s, 0x18, val >> 8);
    rtc_set_memory(s, 0x30, val);
    rtc_set_memory(s, 0x31, val >> 8);
    /* memory between 16MiB and 4GiB */
    if (ram_size > 16 * 1024 * 1024) {
        val = (ram_size - 16 * 1024 * 1024) / 65536;
    } else {
        val = 0;
    }
    if (val > 65535)
        val = 65535;
    rtc_set_memory(s, 0x34, val);
    rtc_set_memory(s, 0x35, val >> 8);
    /* memory above 4GiB */
    val = above_4g_mem_size / 65536;
    rtc_set_memory(s, 0x5b, val);
    rtc_set_memory(s, 0x5c, val >> 8);
    rtc_set_memory(s, 0x5d, val >> 16);

    /* set the number of CPU */
    rtc_set_memory(s, 0x5f, smp_cpus - 1);

    nb = 0; /* use non-determinism */
    switch (nb) {
    case 0:
        break;
    case 1:
        val |= 0x01; /* 1 drive, ready for boot */
        break;
    case 2:
        val |= 0x41; /* 2 drives, ready for boot */
        break;
    }
    val |= 0x02; /* FPU is there */
    val |= 0x04; /* PS/2 mouse installed */
    rtc_set_memory(s, REG_EQUIPMENT_BYTE, val);
}

int main(void)
{
    qverify_start();
    rtc_clock = vm_clock;
    rtc_init(2000);
    pc_cmos_init_for_rtc(global_qverify->rtc_state);

    // Test RTC model
    rtc_verify();
    return 0;
}
