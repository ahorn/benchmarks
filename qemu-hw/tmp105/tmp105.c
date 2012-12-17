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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static inline void check_range(int16_t temperature)
{
    assert((int16_t) 0xd800 <= temperature);
    assert(temperature <= (int16_t) 0x7d00);
}

static inline void check_temperature(TMP105State *s)
{
    /* VC: Temperature measurements are in the range -40 C to +125 C. */
    check_range(s->temperature);

    /* VC: The least significant four bits of the temperature
     *     register are always zero. */
    assert((s->temperature & 0xf) == 0);
}

static inline void check_limits(TMP105State *s)
{
    /* VC: Temperature thresholds must be in the range -40 C to +125 C. */
    check_range(s->limit[0]);
    check_range(s->limit[1]);

    /* VC: T_LOW must be strictly less than T_HIGH.
     *
     * According to the data sheet, all 12 bits of the T_HIGH and T_LOW
     * registers are used in the comparisons for the alarm "even if the
     * converter is configured for 9-bit resolution". Thus, we do not
     * round threshold values to match the resolution. The LM75 Linux
     * driver developer appears to have applied the same reasoning who
     * is assumed to have had access to the hardware.
     */
    assert(s->limit[0] < s->limit[1]);

    /* VC: The least significant four bits of T_LOW are always zero. */
    assert((s->limit[0] & 0xf) == 0);

    /* VC: The least significant four bits of T_HIGH are always zero. */
    assert((s->limit[1] & 0xf) == 0);
}

static inline void check_config(TMP105State *s)
{
    /* VC: When the configuration register is read, bit 7 is always zero. */
    assert(((s->config >> 7) & 1) == 0);
}

static void tmp105_interrupt_update(TMP105State *s)
{
    qemu_set_irq(s->pin, s->alarm ^ ((~s->config >> 2) & 1));	/* POL */
}
static void tmp105_alarm_update(TMP105State *s)
{
    /* VC: Bit 7 of configuration register must only be enabled as long as
     *     bit 0 is also enabled.
     *
     *     Note that this VC does not allow to enable bit 7 while
     *     simultaneously disabling bit 0.
     */
    assert(!(((s->config >> 7) & 1) == 1) || (((s->config >> 0) & 1) == 1));

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
        fprintf(stderr, "%s: values is out of range (%i.%03i C)\n",
                        __FUNCTION__, temp / 1000, temp % 1000);
        exit(-1);
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
         * of the temperature register must be preceded by a write of a "1"
         * to the "one-shot" bit in the configuration register.
         */
        assert(((s->config & 1) == 0) || s->os_trigger);
        s->os_trigger = false;

        s->buf[s->len ++] = (((uint16_t) s->temperature) >> 8);
        s->buf[s->len ++] = (((uint16_t) s->temperature) >> 0) &
                (0xf0 << ((~s->config >> 5) & 3));		/* R */
        break;

    case TMP105_REG_CONFIG:
        s->buf[s->len ++] = s->config;
        break;

    case TMP105_REG_T_LOW:
        s->buf[s->len ++] = ((uint16_t) s->limit[0]) >> 8;
        s->buf[s->len ++] = ((uint16_t) s->limit[0]) >> 0;
        break;

    case TMP105_REG_T_HIGH:
        s->buf[s->len ++] = ((uint16_t) s->limit[1]) >> 8;
        s->buf[s->len ++] = ((uint16_t) s->limit[1]) >> 0;
        break;
    }
}

static void tmp105_write(TMP105State *s)
{
    switch (s->pointer & 3) {
    case TMP105_REG_TEMPERATURE:
        /* VC: The temperature register must never be written. */
        assert(0);
        break;

    case TMP105_REG_CONFIG:
        check_config(s);

        s->os_trigger = (bool) (s->buf[0] & 0x80);

        /* VC: No more than one byte must be written after selecting the
         *     configuration register.
         */
        assert(s->len <= 2);

        if (s->buf[0] & ~s->config & (1 << 0))			/* SD */
            printf("%s: TMP105 shutdown\n", __FUNCTION__);

        s->config = s->buf[0];
        s->faults = tmp105_faultq[(s->config >> 3) & 3];	/* F */
        tmp105_alarm_update(s);

        check_config(s);

        break;

    case TMP105_REG_T_LOW:
    case TMP105_REG_T_HIGH:
        /* VC: No more than two bytes must be written after selecting
         *     either register T_LOW or T_HIGH.
         */
        assert(s->len <= 3);

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
        assert(s->len < 2);
        break;

    case TMP105_REG_CONFIG:
        /* VC: At most one bytes must be read for configuration data. */
        assert(s->len < 1);
        break;

    case TMP105_REG_T_LOW:
    case TMP105_REG_T_HIGH:
        /* VC: At most two bytes must be read for temperature thresholds. */
        assert(s->len < 2);
        break;
    }

    if (s->len < 2) {
        return s->buf[s->len ++];
    }
}

int tmp105_tx(I2CSlave *i2c, uint8_t data)
{
    TMP105State *s = (TMP105State *) i2c;

    if (s->len == 0) {
        /* VC: The value in the pointer register must be between
         *     zero and four inclusive.
         */ 
        assert(0 <= data);
        assert(data <= 4);

        s->pointer = data;
        s->len ++;
    } else {
        if (s->len <= 2) {
            s->buf[s->len - 1] = data;
        }
        s->len ++;
        tmp105_write(s);
    }

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

    tmp105_interrupt_update(s);
}

