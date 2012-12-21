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

extern void tmp105_read(TMP105State *s);
extern void tmp105_write(TMP105State *s);

struct TMP105State temp105_dev;


void
reset_dev (void) {
    I2CSlave* i2c_slave = (I2CSlave*) &temp105_dev;
    tmp105_reset(i2c_slave);
}


// These functions are based on i2c-core.c:i2c_smbus_xfer_emulated
s32
i2c_smbus_read_byte_data (const struct i2c_client *client,
                          u8 command)
{
    assert (command == LM75_REG_CONF);

    temp105_dev.pointer = command;

    // -- Ignoring events for now
    tmp105_read (&temp105_dev);
    assert (temp105_dev.len == 1);

    return temp105_dev.buf[0];
}
EXPORT_SYMBOL(i2c_smbus_read_byte_data);

s32
i2c_smbus_write_byte_data (const struct i2c_client *client,
			   u8 command,
                           u8 value)
{
    assert (command == LM75_REG_CONF);

    temp105_dev.pointer = command;
    temp105_dev.buf[0] = value;
    temp105_dev.len = 2; // originally is 2 (+address)

    // -- Ignoring events for now
    tmp105_write (&temp105_dev);

    return 0;
}

s32
i2c_smbus_read_word_data (const struct i2c_client *client,
			  u8 command)
{
    assert (command != LM75_REG_CONF);
    temp105_dev.pointer = command;

    // -- Ignoring events for now
    tmp105_read (&temp105_dev);
    assert (temp105_dev.len == 2);

    return temp105_dev.buf[0] | (temp105_dev.buf[1] << 8);
}
extern s32
i2c_smbus_write_word_data (const struct i2c_client *client,
			   u8 command,
                           u16 value)
{
    assert (command != LM75_REG_CONF);

    temp105_dev.pointer = command;
    temp105_dev.buf[0] = value & 0xff;
    temp105_dev.buf[1] = value >> 8;
    temp105_dev.len = 3; // originally is 3 (+address)

    // -- Ignoring events for now
    tmp105_write (&temp105_dev);

    return 0;
}

