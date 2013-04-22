/*
 * Texas Instruments TMP105 temperature sensor.
 *
 * Copyright (C) 2008 Nokia Corporation
 * Written by Andrzej Zaborowski <andrew@openedhand.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 or
 * (at your option) version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "i2c.h"
#include "tmp105.h"

#ifndef _SYS_
    #include <stdlib.h>
    #include <stdio.h>
#endif
#ifndef _CBMC_
#include <assert.h>
#endif

static inline void check_range(int16_t temperature)
{
    assert((int16_t) 0xd800 <= temperature);
    assert(temperature <= (int16_t) 0x7d00);
}

static inline void check_temperature(TMP105State *s)
{
#ifdef I2C_BENCHMARK_PROP_1
    /* VC: Temperature measurements are in the range -40 C to +125 C. */
    check_range(s->temperature);
#endif

#ifdef I2C_BENCHMARK_PROP_2
    /* VC: The least significant four bits of the temperature
     *     register are always zero. */
    assert((s->temperature & 0xf) == 0);
#endif
}

static inline void check_limits(TMP105State *s)
{
#ifdef I2C_BENCHMARK_PROP_11
    /* VC: Temperature thresholds must be in the range -40 C to +125 C. */
    check_range(s->limit[0]);
    check_range(s->limit[1]);
#endif

    /* VC: T_LOW must be strictly less than T_HIGH.
     *
     * According to the data sheet, all 12 bits of the T_HIGH and T_LOW
     * registers are used in the comparisons for the alarm "even if the
     * converter is configured for 9-bit resolution". Thus, we do not
     * round threshold values to match the resolution. The LM75 Linux
     * driver developer appears to have applied the same reasoning who
     * is assumed to have had access to the hardware.
     */
#ifdef I2C_BENCHMARK_PROP_12
    assert(s->limit[0] < s->limit[1]);
#endif

#ifdef I2C_BENCHMARK_PROP_13
    /* VC: The least significant four bits of T_LOW are always zero. */
    assert((s->limit[0] & 0xf) == 0);

    /* VC: The least significant four bits of T_HIGH are always zero. */
    assert((s->limit[1] & 0xf) == 0);
#endif
}

static inline void check_config(TMP105State *s)
{
    /* VC: When the configuration register is read, bit 7 is always zero. */
    assert(((s->config >> 7) & 1) == 0);
}

static void tmp105_interrupt_update(TMP105State *s)
{
#ifndef _I2C_NO_IRQ_
    qemu_set_irq(s->pin, s->alarm ^ ((~s->config >> 2) & 1));	/* POL */
#endif
}

static void tmp105_alarm_update(TMP105State *s)
{
    /* VC: Bit 7 of configuration register must only be enabled as long as
     *     bit 0 is also enabled.
     *
     *     Note that this VC does not allow to enable bit 7 while
     *     simultaneously disabling bit 0.
     */
#ifdef I2C_BENCHMARK_PROP_17
    assert(!(((s->config >> 7) & 1) == 1) || (((s->config >> 0) & 1) == 1));
#endif

    if ((s->config >> 0) & 1) {					/* SD */
        if ((s->config >> 7) & 1)				/* OS */
            s->config &= ~(1 << 7);				/* OS */
        else
            return;
    }

    if ((s->config >> 1) & 1) {					/* TM */
        if (s->temperature >= s->limit[1])
            s->alarm = 1;
        else if (s->temperature < s->limit[0])
            s->alarm = 1;
    } else {
        if (s->temperature >= s->limit[1])
            s->alarm = 1;
        else if (s->temperature < s->limit[0])
            s->alarm = 0;
    }

    tmp105_interrupt_update(s);
}

/* Units are 0.001 centigrades relative to 0 C.  */
void tmp105_set(I2CSlave *i2c, int temp)
{
    TMP105State *s = (TMP105State *) i2c;

    if (temp >= 128000 || temp < -128000) {
        #ifndef _SYS_
        fprintf(stderr, "%s: values is out of range (%i.%03i C)\n",
                        __FUNCTION__, temp / 1000, temp % 1000);
        exit(-1);
        #else
            assert(0);
        #endif
    }

    s->temperature = ((int16_t) (temp * 0x800 / 128000)) << 4;

    tmp105_alarm_update(s);
}

static const int tmp105_faultq[4] = { 1, 2, 4, 6 };

static void tmp105_read(TMP105State *s)
{
    s->len = 0;

    if ((s->config >> 1) & 1) {					/* TM */
        s->alarm = 0;
        tmp105_interrupt_update(s);
    }

    switch (s->pointer & 3) {
    case TMP105_REG_TEMPERATURE:
        check_temperature(s);

        /* VC: When the temperature sensor is in shutdown mode, each read
         * of the temperature register must be preceded by a write of "1"
         * to the "one-shot" (OS) bit in the configuration register. Conversely,
         * if a "1" is written the OS bit, the temperature sensor must be in
         * shutdown mode. Equivalently, the VC is that the OS bit is "1" if
         * and only if the temperature sensor is in shutdown mode.
         */
#ifdef I2C_BENCHMARK_PROP_16
        assert(((s->config & 1u) == 1u) == s->os_trigger);
#endif
        s->os_trigger = false;

        s->buf[s->len ++] = (((uint16_t) s->temperature) >> 8);
#ifdef I2C_BENCHMARK_PROP_10
        s->buf_len_info = s->len;
#endif
        s->buf[s->len ++] = (((uint16_t) s->temperature) >> 0) &
                (0xf0 << ((~s->config >> 5) & 3));		/* R */
        break;

    case TMP105_REG_CONFIG:
#ifdef I2C_BENCHMARK_PROP_10
        s->buf_len_info = s->len;
#endif
        s->buf[s->len ++] = s->config;
        break;

    case TMP105_REG_T_LOW:
        s->buf[s->len ++] = ((uint16_t) s->limit[0]) >> 8;
#ifdef I2C_BENCHMARK_PROP_10
        s->buf_len_info = s->len;
#endif
        s->buf[s->len ++] = ((uint16_t) s->limit[0]) >> 0;
        break;

    case TMP105_REG_T_HIGH:
        s->buf[s->len ++] = ((uint16_t) s->limit[1]) >> 8;
#ifdef I2C_BENCHMARK_PROP_10
        s->buf_len_info = s->len;
#endif
        s->buf[s->len ++] = ((uint16_t) s->limit[1]) >> 0;
        break;
    }
}

static void tmp105_write(TMP105State *s)
{
    switch (s->pointer & 3) {
    case TMP105_REG_TEMPERATURE:
        /* VC: The temperature register must never be written. */
#ifdef I2C_BENCHMARK_PROP_3
        assert(0);
#endif
        break;

    case TMP105_REG_CONFIG:
#ifdef I2C_BENCHMARK_PROP_14
        check_config(s);
#endif

        s->os_trigger = (bool) (s->buf[0] & 0x80);

        /* VC: No more than one byte must be written after selecting the
         *     configuration register.
         */
#ifdef I2C_BENCHMARK_PROP_4
        assert(s->len <= 2);
#endif

        #ifndef _SYS_
        if (s->buf[0] & ~s->config & (1 << 0))			/* SD */
            printf("%s: TMP105 shutdown\n", __FUNCTION__);
        #endif

        s->config = s->buf[0];
        s->faults = tmp105_faultq[(s->config >> 3) & 3];	/* F */
        tmp105_alarm_update(s);

#ifdef I2C_BENCHMARK_PROP_15
        check_config(s);
#endif

        break;

    case TMP105_REG_T_LOW:
    case TMP105_REG_T_HIGH:
        /* VC: No more than two bytes must be written after selecting
         *     either register T_LOW or T_HIGH.
         */
#ifdef I2C_BENCHMARK_PROP_5
        assert(s->len <= 3);
#endif

        if (s->len == 3) {
            s->limit[s->pointer & 1] = (int16_t)
                    ((((uint16_t) s->buf[0]) << 8) | s->buf[1]);

            check_limits(s);
        }

        tmp105_alarm_update(s);
        break;
    }
}

int tmp105_rx(I2CSlave *i2c)
{
    TMP105State *s = (TMP105State *) i2c;

    switch (s->pointer & 3) {
    case TMP105_REG_TEMPERATURE:
        /* VC: At most two bytes must be read for temperature measurements.
         *
         * That is, the reading of the least significant byte is optional.
         */
#ifdef I2C_BENCHMARK_PROP_6
        assert(s->len < 2);
#endif
        break;

    case TMP105_REG_CONFIG:
        /* VC: At most one bytes must be read for configuration data. */
#ifdef I2C_BENCHMARK_PROP_7
        assert(s->len < 1);
#endif
        break;

    case TMP105_REG_T_LOW:
    case TMP105_REG_T_HIGH:
        /* VC: At most two bytes must be read for temperature thresholds. */
#ifdef I2C_BENCHMARK_PROP_8
        assert(s->len < 2);
#endif
        break;
    }

    if (s->len < 2) {
        return s->buf[s->len ++];
    }
}

int tmp105_tx(I2CSlave *i2c, uint8_t data)
{
    TMP105State *s = (TMP105State *) i2c;
#ifdef __EXPOSE_BUG__
    // Orginal bug for testing
    if (!s->len ++) {
       s->pointer = data;
    } else {
        if (s->len <= 2) {
#ifdef I2C_BENCHMARK_PROP_10
            assert((s->len != 2) || (s->buf_len_info == 1));
            s->buf_len_info = s->len;
#endif
            s->buf[s->len - 1] = data;
        } 
        tmp105_write(s);
     } 
#else
    /* Fixed bug:
     *    http://lists.gnu.org/archive/html/qemu-devel/2012-12/msg01455.html
     */
    if (s->len == 0) {
        /* VC: The value in the pointer register must be between
         *     zero and four inclusive.
         */ 
        s->pointer = data;
        s->len ++;
    } else {
        if (s->len <= 2) {

           /* VC: If buf[1] is written, buf[0] must have been written, too */
#ifdef I2C_BENCHMARK_PROP_10
            assert((s->len != 2) || (s->buf_len_info == 1));
            s->buf_len_info = s->len;
#endif
            s->buf[s->len - 1] = data;
        }
        s->len ++;
        tmp105_write(s);
    }
#endif
    
    return 0;
}

void tmp105_event(I2CSlave *i2c, enum i2c_event event)
{
    TMP105State *s = (TMP105State *) i2c;

    if (event == I2C_START_RECV)
        tmp105_read(s);

    s->len = 0;
}

void tmp105_reset(I2CSlave *i2c)
{
    TMP105State *s = (TMP105State *) i2c;

    s->temperature = 0;
    s->pointer = 0;
    s->config = 0;
    s->faults = tmp105_faultq[(s->config >> 3) & 3];
    s->alarm = 0;
    s->limit[0] = 0x4b00; /* T_LOW  = 75 C */
    s->limit[1] = 0x5000; /* T_HIGH = 80 C */
    s->os_trigger = false;
#ifdef I2C_BENCHMARK_PROP_10
    s->buf_len_info = -1;
#endif

    tmp105_interrupt_update(s);
}

