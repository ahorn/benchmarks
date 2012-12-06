/*
 * Unit tests for TMP105 temperature sensor hardware model
 *
 * Copyright (C) 2012 Alex Horn <alex.horn@cs.ox.ac.uk>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 */
#include "tmp105.h"

#include <stdbool.h>
#include <assert.h>

#define assert_cmpint(value, op, delta) assert(value op delta)

static I2CSlave *i2c_slave;
static bool alarm_rang = false;

/* Reads a single byte */
static uint16_t read_byte(void)
{
    uint8_t byte;

    tmp105_event(i2c_slave, I2C_START_RECV);
    byte = tmp105_rx(i2c_slave);
    tmp105_event(i2c_slave, I2C_FINISH);

    return byte;
}

/* Reads a word whose MSB is transmitted first */
static uint16_t read_word(void)
{
    uint16_t word;

    tmp105_event(i2c_slave, I2C_START_RECV);
    word = tmp105_rx(i2c_slave) << 8;
    word |= tmp105_rx(i2c_slave) << 0;
    tmp105_event(i2c_slave, I2C_FINISH);

    return word;
}

/* Writes a single byte */
static void write_byte(uint8_t byte)
{
    tmp105_event(i2c_slave, I2C_START_SEND);
    tmp105_tx(i2c_slave, byte);
    tmp105_event(i2c_slave, I2C_FINISH);
}

/* Writes two consecutive bytes */
static void write_word(uint8_t byte0, uint8_t byte1)
{
    tmp105_event(i2c_slave, I2C_START_SEND);
    tmp105_tx(i2c_slave, byte0);
    tmp105_tx(i2c_slave, byte1);
    tmp105_event(i2c_slave, I2C_FINISH);
}

/*
 * Tests reading temperature with 9-bit precision (0.5 C)
 */
static void test_read_with_default_precision(void)
{
    int16_t temperature;

    /* boiling water, +100 C */
    tmp105_set(i2c_slave, 100000);

    temperature = read_word();
    assert_cmpint(temperature, ==, 0x06400);
}

/*
 * Tests alarm with polarity (POL) bit equal to zero.
 */
static void test_alarm(void)
{
    int16_t temperature;

    /* above 80 C */
    tmp105_set(i2c_slave, 81000);

    /* POL=0 inverts alarm signal */
    assert_cmpint(alarm_rang, ==, false);

    /* below 75 C */
    tmp105_set(i2c_slave, 74000);

    /* POL=0 inverts alarm signal */
    assert_cmpint(alarm_rang, ==, true);
}

/*
 * Tests 11-bit precision (0.125 C) of TMP105 temperature sensor
 */
static void test_eleven_bit_precision(void)
{
    TMP105State *tmp105_state;
    int16_t temperature;
    uint8_t precision;

    /* setup snow slush, +0.125 C */
    tmp105_set(i2c_slave, 125);

    /* check internal temperature register */
    tmp105_state = (TMP105State *) i2c_slave;
    assert_cmpint(tmp105_state->temperature, ==, 0x20);

    /* expect ice! */
    temperature = read_word();
    assert_cmpint(temperature, ==, 0);

    /* configure 11 bit (0.125 C) precision */
    precision = 0x40;                                       /* R1=1 and R0=0 */
    write_word(TMP105_REG_CONFIG, precision);

    /* select temperature register */
    write_byte(TMP105_REG_TEMPERATURE);

    /* expect snow slush */
    temperature = read_word();
    assert_cmpint(temperature, ==, 0x20);
}

/*
 * Tests writing and then reading configuration register
 */
static void test_change_config(void)
{
    uint8_t config;
    uint8_t new_config;

    /* select configuration register */
    write_byte(TMP105_REG_CONFIG);

    /* expect initial configuration */
    config = read_byte();
    assert_cmpint(config, ==, 0);

    /* write configuration register */
    write_word(TMP105_REG_CONFIG, 0x40);

    /* expect new configuration */
    config = read_byte();
    assert_cmpint(config, ==, 0x40);
}

static void tmp105_handler(void *opaque, int n, int level)
{
    alarm_rang = level > 0 ? true : false;
    assert_cmpint(n, ==, 3);
}

int main(void)
{
    TMP105State tmp105_state;
    IRQState irq_state;

    /* setup IRQ */
    irq_state.n = 3;
    irq_state.handler = tmp105_handler;

    /* setup TMP105 hardware model */
    tmp105_state.pin = &irq_state;

    /* setup global variable */
    i2c_slave = (I2CSlave*) &tmp105_state;

    /* run tests */
    tmp105_reset(i2c_slave);
    test_read_with_default_precision();

    tmp105_reset(i2c_slave);
    test_alarm();

    tmp105_reset(i2c_slave);
    test_eleven_bit_precision();

    tmp105_reset(i2c_slave);
    test_change_config();

    return 0;
}

/*
int main(int argc, char **argv)
{
    TMP105State state;
    i2c_slave = (I2CSlave*) &state;

    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/tmp105/eleven_bit_precision", test_eleven_bit_precision);

    return g_test_run();
}
*/
