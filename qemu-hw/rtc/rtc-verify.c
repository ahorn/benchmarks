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
    outb(base + 0, reg);
    return inb(base + 1);
}

static void cmos_write(uint8_t reg, uint8_t val)
{
    outb(base + 0, reg);
    outb(base + 1, val);
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
    /* Enable binary-coded decimal (BCD) mode and SET flag in Register B*/
    cmos_write(RTC_REG_B, (cmos_read(RTC_REG_B) & ~REG_B_DM) | REG_B_SET);
    cmos_write(RTC_HOURS, 0x03);
    cmos_write(RTC_REG_A, 0x26);
    cmos_write(RTC_REG_B, cmos_read(RTC_REG_B) & ~REG_B_SET);

    assert_cmpint(cmos_read(RTC_HOURS), ==, 0x03);
}

void rtc_verify(void)
{
    set_year_20xx();
    set_year_1980();
    register_b_set_flag();
}
