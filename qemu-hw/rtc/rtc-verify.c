/*
 * Test the MC146818 real-time clock
 *
 * Based on work by Anthony Liguori <aliguori@us.ibm.com>.
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */
#include "rtc-verify.h"
#include "qverify.h"
#include "qemu-timer.h"
#include "mc146818rtc_regs.h"

#include <assert.h>
#include <string.h>

#define assert_cmpint(value, op, delta) assert(value op delta)

static uint8_t base = 0x70;

static uint8_t cmos_read(uint8_t reg)
{
    outb(reg, base + 0);
    return inb(base + 1);
}

static void cmos_write(uint8_t reg, uint8_t val)
{
    outb(reg, base + 0);
    outb(val, base + 1);
}

static int bcd2dec(int value)
{
    return (((value >> 4) & 0x0F) * 10) + (value & 0x0F);
}

static int tm_cmp(struct tm *lhs, struct tm *rhs)
{
    time_t a, b;

    a = mktime(lhs);
    b = mktime(rhs);

    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    }

    return 0;
}

static void cmos_get_date_time(struct tm *date)
{
    int base_year = 2000, hour_offset;
    int sec, min, hour, mday, mon, year;
    time_t ts;
    struct tm dummy;

    sec = cmos_read(RTC_SECONDS);
    min = cmos_read(RTC_MINUTES);
    hour = cmos_read(RTC_HOURS);
    mday = cmos_read(RTC_DAY_OF_MONTH);
    mon = cmos_read(RTC_MONTH);
    year = cmos_read(RTC_YEAR);

    if ((cmos_read(RTC_REG_B) & REG_B_DM) == 0) {
        sec = bcd2dec(sec);
        min = bcd2dec(min);
        hour = bcd2dec(hour);
        mday = bcd2dec(mday);
        mon = bcd2dec(mon);
        year = bcd2dec(year);
        hour_offset = 80;
    } else {
        hour_offset = 0x80;
    }

    if ((cmos_read(0x0B) & REG_B_24H) == 0) {
        if (hour >= hour_offset) {
            hour -= hour_offset;
            hour += 12;
        }
    }

    ts = time(NULL);
    localtime_r(&ts, &dummy);

    date->tm_isdst = dummy.tm_isdst;
    date->tm_sec = sec;
    date->tm_min = min;
    date->tm_hour = hour;
    date->tm_mday = mday;
    date->tm_mon = mon - 1;
    date->tm_year = base_year + year - 1900;
    date->tm_gmtoff = 0;

    ts = mktime(date);
}

#define ABS(a)	   (((a) < 0) ? -(a) : (a))

static void check_time(int wiggle)
{
    struct tm start, date[4], end;
    struct tm *datep;
    time_t ts;

    /*
     * This check assumes a few things.  First, we cannot guarantee that we get
     * a consistent reading from the wall clock because we may hit an edge of
     * the clock while reading.  To work around this, we read four clock readings
     * such that at least two of them should match.  We need to assume that one
     * reading is corrupt so we need four readings to ensure that we have at
     * least two consecutive identical readings
     *
     * It's also possible that we'll cross an edge reading the host clock so
     * simply check to make sure that the clock reading is within the period of
     * when we expect it to be.
     */

    ts = time(NULL);
    gmtime_r(&ts, &start);

    cmos_get_date_time(&date[0]);
    cmos_get_date_time(&date[1]);
    cmos_get_date_time(&date[2]);
    cmos_get_date_time(&date[3]);

    ts = time(NULL);
    gmtime_r(&ts, &end);

    if (tm_cmp(&date[0], &date[1]) == 0) {
        datep = &date[0];
    } else if (tm_cmp(&date[1], &date[2]) == 0) {
        datep = &date[1];
    } else if (tm_cmp(&date[2], &date[3]) == 0) {
        datep = &date[2];
    } else {
        assert(0);
    }

    if (!(tm_cmp(&start, datep) <= 0 && tm_cmp(datep, &end) <= 0)) {
        long t, s;

        start.tm_isdst = datep->tm_isdst;

        t = (long)mktime(datep);
        s = (long)mktime(&start);

        assert_cmpint(ABS(t - s), <=, wiggle);
    }
}

static int wiggle = 2;

static void check_time_with_current_mode(void)
{
    check_time(wiggle);

    cmos_write(RTC_REG_B, cmos_read(RTC_REG_B) | REG_B_SET);
    cmos_write(RTC_REG_B, cmos_read(RTC_REG_B) & ~REG_B_SET);

    check_time(wiggle);
}

static void set_year_20xx(void)
{
    /* Set BCD mode */
    cmos_write(RTC_REG_B, (cmos_read(RTC_REG_B) & ~REG_B_DM) | REG_B_SET);
    cmos_write(RTC_REG_A, 0x76);
    cmos_write(RTC_YEAR, 0x11);
    cmos_write(RTC_CENTURY, 0x20);
    cmos_write(RTC_MONTH, 0x02);
    cmos_write(RTC_DAY_OF_MONTH, 0x02);
    cmos_write(RTC_HOURS, 0x02);
    cmos_write(RTC_MINUTES, 0x04);
    cmos_write(RTC_SECONDS, 0x58);
    cmos_write(RTC_REG_A, 0x26);
    cmos_write(RTC_REG_B, cmos_read(RTC_REG_B) & ~REG_B_SET);

    assert_cmpint(cmos_read(RTC_HOURS), ==, 0x02);
    assert_cmpint(cmos_read(RTC_MINUTES), ==, 0x04);
    assert_cmpint(cmos_read(RTC_SECONDS), >=, 0x58);
    assert_cmpint(cmos_read(RTC_DAY_OF_MONTH), ==, 0x02);
    assert_cmpint(cmos_read(RTC_MONTH), ==, 0x02);
    assert_cmpint(cmos_read(RTC_YEAR), ==, 0x11);
    assert_cmpint(cmos_read(RTC_CENTURY), ==, 0x20);

    /* Set a date in 2080 to ensure there is no year-2038 overflow.  */
    cmos_write(RTC_REG_B, (cmos_read(RTC_REG_B) & ~REG_B_DM) | REG_B_SET);
    cmos_write(RTC_REG_A, 0x76);
    cmos_write(RTC_YEAR, 0x80);
    cmos_write(RTC_REG_A, 0x26);
    cmos_write(RTC_REG_B, cmos_read(RTC_REG_B) & ~REG_B_SET);

    assert_cmpint(cmos_read(RTC_HOURS), ==, 0x02);
    assert_cmpint(cmos_read(RTC_MINUTES), ==, 0x04);
    assert_cmpint(cmos_read(RTC_SECONDS), >=, 0x58);
    assert_cmpint(cmos_read(RTC_DAY_OF_MONTH), ==, 0x02);
    assert_cmpint(cmos_read(RTC_MONTH), ==, 0x02);
    assert_cmpint(cmos_read(RTC_YEAR), ==, 0x80);
    assert_cmpint(cmos_read(RTC_CENTURY), ==, 0x20);

    cmos_write(RTC_REG_B, (cmos_read(RTC_REG_B) & ~REG_B_DM) | REG_B_SET);
    cmos_write(RTC_REG_A, 0x76);
    cmos_write(RTC_REG_A, 0x76);
    cmos_write(RTC_YEAR, 0x11);
    cmos_write(RTC_REG_A, 0x26);
    cmos_write(RTC_REG_B, cmos_read(RTC_REG_B) & ~REG_B_SET);

    assert_cmpint(cmos_read(RTC_HOURS), ==, 0x02);
    assert_cmpint(cmos_read(RTC_MINUTES), ==, 0x04);
    assert_cmpint(cmos_read(RTC_SECONDS), >=, 0x58);
    assert_cmpint(cmos_read(RTC_DAY_OF_MONTH), ==, 0x02);
    assert_cmpint(cmos_read(RTC_MONTH), ==, 0x02);
    assert_cmpint(cmos_read(RTC_YEAR), ==, 0x11);
    assert_cmpint(cmos_read(RTC_CENTURY), ==, 0x20);
}

static void set_year_1980(void)
{
    /* Set BCD mode */
    cmos_write(RTC_REG_B, (cmos_read(RTC_REG_B) & ~REG_B_DM) | REG_B_SET);
    cmos_write(RTC_REG_A, 0x76);
    cmos_write(RTC_YEAR, 0x80);
    cmos_write(RTC_CENTURY, 0x19);
    cmos_write(RTC_MONTH, 0x02);
    cmos_write(RTC_DAY_OF_MONTH, 0x02);
    cmos_write(RTC_HOURS, 0x02);
    cmos_write(RTC_MINUTES, 0x04);
    cmos_write(RTC_SECONDS, 0x58);
    cmos_write(RTC_REG_A, 0x26);
    cmos_write(RTC_REG_B, cmos_read(RTC_REG_B) & ~REG_B_SET);

    assert_cmpint(cmos_read(RTC_HOURS), ==, 0x02);
    assert_cmpint(cmos_read(RTC_MINUTES), ==, 0x04);
    assert_cmpint(cmos_read(RTC_SECONDS), >=, 0x58);
    assert_cmpint(cmos_read(RTC_DAY_OF_MONTH), ==, 0x02);
    assert_cmpint(cmos_read(RTC_MONTH), ==, 0x02);
    assert_cmpint(cmos_read(RTC_YEAR), ==, 0x80);
    assert_cmpint(cmos_read(RTC_CENTURY), ==, 0x19);
}

static void register_b_set_flag(void)
{
    uint8_t abcd;
#ifdef __CBMC_TEST_HW__
    __CPROVER_assume( abcd >= 0 && abcd < 23 );
#endif    
#ifndef __KLEE_TEST_HW__
    klee_make_symbolic(&abcd, sizeof(abcd), "abcd");
    klee_assume( abcd >= 0 && abcd < 23 );
#endif

    /* Enable binary-coded decimal (BCD) mode and SET flag in Register B*/
    cmos_write(RTC_REG_B, (cmos_read(RTC_REG_B) & ~REG_B_DM) | REG_B_SET);
    cmos_write(RTC_REG_A, 0x76);
    
#if defined (__CBMC_TEST_HW__) || defined (__KLEE_TEST_HW__)
    //cmos_write(RTC_HOURS, abcd);
    //cmos_write(RTC_HOURS, 0x03);
#else
    cmos_write(RTC_HOURS, 0x03);
#endif

    cmos_write(RTC_HOURS, 0x03);
    cmos_write(RTC_REG_A, 0x26);

    /* Exposes bug:
     *    http://git.qemu.org/?p=qemu.git;a=commit;h=02c6ccc6dde90dcbf5975b1cfe2ab199e525ec11
     *
     * See also assert_equal_copy_data() in file mc146818rtc.c
     */
#ifndef __EXPOSE_BUG__ 
    assert_cmpint(cmos_read(RTC_HOURS), ==, 0x03);
    assert_cmpint(cmos_read(RTC_HOURS), ==, abcd);
#endif
    cmos_write(RTC_REG_B, cmos_read(RTC_REG_B) & ~REG_B_SET);
#ifndef __EXPOSE_BUG__ 
    assert_cmpint(cmos_read(RTC_HOURS), ==, 0x03);
    assert_cmpint(cmos_read(RTC_HOURS), ==, abcd);
#endif
}

static void check_clock_cbmc(void)
{
    /* Set BCD mode */
    cmos_write(RTC_REG_B, (cmos_read(RTC_REG_B) & ~REG_B_DM) | REG_B_SET);
    cmos_write(RTC_REG_A, 0x76);
    
    /* Non-deterministic variables */
    uint8_t symb_year, symb_century, symb_month, symb_day,
            symb_hour, symb_min, symb_sec;
#ifdef __CBMC_TEST_HW__    
    __CPROVER_assume( symb_year >= 0  && symb_year < 100 );
    __CPROVER_assume( symb_month >= 1 && symb_month <= 12 );
    __CPROVER_assume( symb_day >= 1 && symb_day <= 31 );
    __CPROVER_assume( symb_hour >= 0 && symb_hour < 23 );
    __CPROVER_assume( symb_min >= 0 && symb_min < 60 );
    __CPROVER_assume( symb_sec >= 0 && symb_sec < 60 );
#endif 

#ifdef __KLEE_TEST_HW__
    klee_make_symbolic(&symb_year, sizeof(symb_year), "symb_year");
    klee_make_symbolic(&symb_month, sizeof(symb_month), "symb_month");
    klee_make_symbolic(&symb_day, sizeof(symb_day), "symb_day");
    klee_make_symbolic(&symb_hour, sizeof(symb_hour), "symb_hour");
    klee_make_symbolic(&symb_min, sizeof(symb_min), "symb_min");
    klee_make_symbolic(&symb_sec, sizeof(symb_sec), "symb_sec");

    klee_assume( symb_year >= 0  && symb_year < 100 );
    klee_assume( symb_month >= 1 && symb_month <= 12 );
    klee_assume( symb_day >= 1 && symb_day <= 31 );
    klee_assume( symb_hour >= 0 && symb_hour < 23 );
    klee_assume( symb_min >= 0 && symb_min < 60 );
    klee_assume( symb_sec >= 0 && symb_sec < 60 );
#endif

    /* Set clock */
    cmos_write(RTC_YEAR, symb_year);
    cmos_write(RTC_CENTURY, symb_century);
    cmos_write(RTC_MONTH, symb_month);
    cmos_write(RTC_DAY_OF_MONTH, symb_day);
    cmos_write(RTC_HOURS, symb_hour);
    cmos_write(RTC_MINUTES, symb_min);
    cmos_write(RTC_SECONDS, symb_sec);
    
    /* Get clock */
    cmos_read(RTC_YEAR);
    cmos_read(RTC_CENTURY);
    cmos_read(RTC_MONTH);
    cmos_read(RTC_DAY_OF_MONTH);
    cmos_read(RTC_HOURS);
    cmos_read(RTC_MINUTES);
    cmos_read(RTC_SECONDS);

    cmos_write(RTC_REG_A, 0x26);
    cmos_write(RTC_REG_B, cmos_read(RTC_REG_B) & ~REG_B_SET);
}


static void simulate_bugs() {
    uint8_t aaa;
    inb(base + 1);
    outb(aaa, base + 0); 
}

void rtc_verify(void)
{
#if ! (defined (__CBMC_TEST_HW__) || defined (__KLEE_TEST_HW__))
    check_time_with_current_mode();
    set_year_20xx();
    set_year_1980();
    register_b_set_flag();
    check_clock_cbmc();
#endif

#ifdef __CBMC_TEST_HW__
#ifndef __EXPOSE_BUG__
    check_clock_cbmc();
#else
    register_b_set_flag();
    //simulate_bugs();
#endif
#else 
    check_time_with_current_mode();
#endif
}
