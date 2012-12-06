/*
 * Texas Instruments TMP105 Temperature Sensor
 *
 * Browse the data sheet:
 *
 *    http://www.ti.com/lit/gpn/tmp105
 *
 * Copyright (C) 2012 Alex Horn <alex.horn@cs.ox.ac.uk>
 * Copyright (C) 2008-2012 Andrzej Zaborowski <balrogg@gmail.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later. See the COPYING file in the top-level directory.
 */
#ifndef QEMU_TMP105_H
#define QEMU_TMP105_H

#include "i2c.h"
#include "irq.h"

#include <stdint.h>

typedef struct {
    I2CSlave i2c;
    uint8_t len;
    uint8_t buf[2];
    qemu_irq pin;

    uint8_t pointer;
    uint8_t config;
    int16_t temperature;
    int16_t limit[2];
    int faults;
    uint8_t alarm;
} TMP105State;

/**
 * TMP105Reg:
 * @TMP105_REG_TEMPERATURE: Temperature register
 * @TMP105_REG_CONFIG: Configuration register
 * @TMP105_REG_T_LOW: Low temperature register (also known as T_hyst)
 * @TMP105_REG_T_HIGH: High temperature register (also known as T_OS)
 *
 * The following temperature sensors are
 * compatible with the TMP105 registers:
 * - adt75
 * - ds1775
 * - ds75
 * - lm75
 * - lm75a
 * - max6625
 * - max6626
 * - mcp980x
 * - stds75
 * - tcn75
 * - tmp100
 * - tmp101
 * - tmp105
 * - tmp175
 * - tmp275
 * - tmp75
 **/
typedef enum TMP105Reg {
    TMP105_REG_TEMPERATURE = 0,
    TMP105_REG_CONFIG,
    TMP105_REG_T_LOW,
    TMP105_REG_T_HIGH,
} TMP105Reg;

/**
 * tmp105_set:
 * @i2c: dispatcher to TMP105 hardware model
 * @temp: temperature with 0.001 centigrades units in the range -40 C to +125 C
 *
 * Sets the temperature of the TMP105 hardware model.
 *
 * Bits 5 and 6 (value 32 and 64) in the register indexed by TMP105_REG_CONFIG
 * determine the precision of the temperature. See Table 8 in the data sheet.
 *
 * @see_also: I2C_SLAVE macro
 * @see_also: http://www.ti.com/lit/gpn/tmp105
 */
void tmp105_set(I2CSlave *i2c, int temp);

/**
 * tmp105_reset:
 * @i2c: dispatcher to TMP105 hardware model
 *
 * Reset TMP105 registers to zero.
 */
void tmp105_reset(I2CSlave *i2c);

/**
 * tmp105_event:
 * @i2c: dispatcher to TMP105 hardware model
 * @event: receive, send or nack
 *
 * Either starts or ends an I2C transaction.
 */
void tmp105_event(I2CSlave *i2c, enum i2c_event event);

/**
 * tmp105_rx:
 * @i2c: dispatcher to TMP105 hardware model
 *
 * Returns TMP105 data according to I2C protocol.
 */
int tmp105_rx(I2CSlave *i2c);

/**
 * tmp105_tx:
 * @i2c: dispatcher to TMP105 hardware model
 * @data: byte to be written
 *
 * Writes @data to TMP105 according to I2C protocol.
 */
int tmp105_tx(I2CSlave *i2c, uint8_t data);

#endif
