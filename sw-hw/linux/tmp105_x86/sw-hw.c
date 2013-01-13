/*
 *  QEMU-Linux interface for tmp105 driver.
 *      . Re-implementation of i2c functions (from i2c-core.c)
 *      . Based on QEMU's test tmp105-test.c 
 *
 */

/*  Copyright (C) 1995-2000 Simon G. Vogl
    Copyright (C) 2012 Celina G. Val

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
    MA 02110-1301 USA.							     */

#include <tmp105/tmp105.h>
#include <linux/i2c.h>
#include <linux/export.h>

static struct TMP105State temp105_dev;
static I2CSlave *i2c_slave;
static IRQState irq_state;

static void tmp105_handler(void *opaque, int n, int level)
{
    assert (n == 3);
}

static void
reset_dev (void) {

    /* setup IRQ */
    irq_state.n = 3;
    irq_state.handler = tmp105_handler;

    /* setup TMP105 hardware model */
    temp105_dev.pin = &irq_state;

    i2c_slave = (I2CSlave*) &temp105_dev;
    tmp105_reset(i2c_slave);
}

/* Reads a single byte */
static u8 tmp105_read_byte(void)
{
    u8 byte;

    tmp105_event(i2c_slave, I2C_START_RECV);
    byte = tmp105_rx(i2c_slave);
    tmp105_event(i2c_slave, I2C_FINISH);

    return byte;
}

/* Reads a word whose MSB is transmitted first */
static u16 tmp105_read_word(void)
{
    u16 word;

    tmp105_event(i2c_slave, I2C_START_RECV);
    word = tmp105_rx(i2c_slave) << 8;
    word |= tmp105_rx(i2c_slave) << 0;
    tmp105_event(i2c_slave, I2C_FINISH);

    return word;
}

/* Writes data buffer to the temperature sensor */
static void tmp105_write_array(const u8 *data, unsigned size)
{
    unsigned i;

    tmp105_event(i2c_slave, I2C_START_SEND);
    for (i = 0; i < size; i++) {
        tmp105_tx(i2c_slave, data[i]);
    }
    tmp105_event(i2c_slave, I2C_FINISH);
}

/* Writes a single byte to the temperature sensor */
static void tmp105_write_byte(u8 data)
{
    tmp105_write_array(&data, 1);
}

// These functions are based on i2c-core.c:i2c_smbus_xfer_emulated
s32
i2c_smbus_read_byte_data (const struct i2c_client *client,
                          u8 command)
{
    // Can be different addresses during detect
    //assert (command == LM75_REG_CONF);

    /* select configuration register */
    tmp105_write_byte(command);
    return tmp105_read_byte();
}

s32
i2c_smbus_write_byte_data (const struct i2c_client *client,
			   u8 command,
                           u8 value)
{
    assert (command == LM75_REG_CONF);

    const u8 data[] = {command, value};
    tmp105_write_array(data, 2);

    return 0;
}

s32
i2c_smbus_read_word_data (const struct i2c_client *client,
			  u8 command)
{
    assert (command != LM75_REG_CONF);

    tmp105_write_byte(command);
    return tmp105_read_word();
}

extern s32
i2c_smbus_write_word_data (const struct i2c_client *client,
			   u8 command,
                           u16 value)
{
    assert (command != LM75_REG_CONF);

    /* I2C requires to send the most significant byte first */
    const u8 data[] = {command, /* high */value >> 8, /* low */value & 0xff};
    tmp105_write_array(data, 3);

    return 0;
}

