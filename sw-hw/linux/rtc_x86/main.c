#include <generated/autoconf.h>
#ifndef _CBMC_
    #define assert(expr) \
            if (!(expr)) { \
            printk( "Assertion failed! %s,%s,%s,line=%d\n",\
            #expr,__FILE__,__func__,__LINE__); \
            BUG(); \
            }
#endif

#include <linux/rtc.h>
#include <asm/mc146818rtc.h>		/* register access macros */

/* Linux files */
/* We include it here because we want to propagate the autoconf */
#include <rtc/rtc-cmos.c>   /* Implements generic rtc-cmos.c driver*/
#include <rtc.c>            /* Implements x86 rtc (/kernel) */
#include <bcd.c>
#include <base/platform.c>
//#include <base/driver.c> - conflict with rtc-cmos

/* QEMU Model */
#include <model/mc146818rtc_regs.h>
#include <model/qemu-timer.h>
#include "model/qemu-timer.c"
#include <model/qverify.h>
#include "model/qverify.c"
#include <model/mc146818rtc.h>
#include "model/mc146818rtc.c"

int main (int argc, char** argv) {

    cmos_init();

    struct rtc_time t;
    cmos_read_time (NULL, &t);
    cmos_set_time (NULL, &t);
    get_rtc_time (&t);
    set_rtc_time (&t);
    assert (rtc_is_updating());
    u8 bla = inb (10);
    outb (12, bla);
    assert (bla != 4);

    //struct cmos_rtc *cmos = dev_get_drvdata(dev);
    cmos_exit();

    return 0;
}
