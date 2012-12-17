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
#include <stddef.h>

#define assert_cmpint(value, op, delta) assert((value) op (delta))

static I2CSlave *i2c_slave;
static bool alarm_rang = false;

/* Reads a single byte */
static uint8_t read_byte(void)
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

/* Writes data buffer to the temperature sensor */
static void write(const uint8_t *data, size_t size)
{
    int i;
    tmp105_event(i2c_slave, I2C_START_SEND);
    for (i = 0; i < size; i++) {
        tmp105_tx(i2c_slave, data[i]);
    }
    tmp105_event(i2c_slave, I2C_FINISH);
}

/* Writes a single byte to the temperature sensor */
static void write_byte(uint8_t data)
{
    write(&data, 1);
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
    const uint8_t precision = 0x40;          /* R1=1 and R0=0 */
    const uint8_t data[] = {TMP105_REG_CONFIG, precision};

    /* setup snow slush, +0.125 C */
    tmp105_set(i2c_slave, 125);

    /* check internal temperature register */
    tmp105_state = (TMP105State *) i2c_slave;
    assert_cmpint(tmp105_state->temperature, ==, 0x20);

    /* expect ice! */
    temperature = read_word();
    assert_cmpint(temperature, ==, 0);

    /* configure 11 bit (0.125 C) precision */
    write(data, 2);

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
    /* ideally, use a non-deterministic value except the most significant bit
     * which should be zero unless the temperature sensor is in shutdown mode.
     */
    const uint8_t config = 0x40;

    uint8_t new_config;
    const uint8_t data[] = {TMP105_REG_CONFIG, config};

    /* select configuration register */
    write_byte(TMP105_REG_CONFIG);

    /* expect initial configuration */
    assert_cmpint(read_byte(), ==, 0);

    /* overwrite configuration register */
    write(data, 2);

    /* VC: After writing byte C to the configuration register, the next read of
     *     the configuration register returns a byte C' such that C[i] = C'[i]
     *     where 0 <= i < 7. That is, the first seven bits of C and C' are
     *     pairwise equal.
     */
    new_config = read_byte();
    assert((new_config & 0x7f) == (config & 0x7f));
}

/*
 * Tests writing and then reading T_LOW register
 */
static void test_change_lower_limit(void)
{
    /* ideally, use two non-deterministic bytes */
    const uint8_t lo_limit_h = 0x3a, lo_limit_l = 0x10;

    uint16_t hi_limit, snd_hi_limit, lo_limit;
    const uint8_t data[] = {TMP105_REG_T_LOW, lo_limit_h, lo_limit_l};

    /* save higher limit register value */
    write_byte(TMP105_REG_T_HIGH);
    hi_limit = read_word();

    /* select lower limit register */
    write_byte(TMP105_REG_T_LOW);

    /* expect initial lower limit */
    lo_limit = read_word();
    assert_cmpint(lo_limit, ==, 0x4b00);

    /* overwrite lower limit register value */
    write(data, 3);

    /* VC: After writing a word to the register T_LOW, the next read of T_LOW
     *     returns the same word.
     */
    lo_limit = read_word();
    assert(lo_limit == ((lo_limit_h << 8) | lo_limit_l));

    /* expect T_HIGH to be unchanged */
    write_byte(TMP105_REG_T_HIGH);
    snd_hi_limit = read_word();
    assert_cmpint(hi_limit, ==, snd_hi_limit);
}

/*
 * Tests writing and then reading T_HIGH register
 */
static void test_change_higher_limit(void)
{
    /* ideally, use two non-deterministic bytes */
    const uint8_t hi_limit_h = 0x67, hi_limit_l = 0x80;

    uint16_t hi_limit, lo_limit, snd_lo_limit;
    const uint8_t data[] = {TMP105_REG_T_HIGH, hi_limit_h, hi_limit_l};

    /* save lower limit register value */
    write_byte(TMP105_REG_T_LOW);
    lo_limit = read_word();

    /* select higher limit register */
    write_byte(TMP105_REG_T_HIGH);

    /* expect initial higher limit */
    hi_limit = read_word();
    assert_cmpint(hi_limit, ==, 0x5000);

    /* overwrite higher limit register value */
    write(data, 3);

    /* VC: After writing a word to the register T_HIGH, the next read of T_HIGH
     *     returns the same word.
     */
    hi_limit = read_word();
    assert(hi_limit == ((hi_limit_h << 8) | hi_limit_l));

    /* expect T_LOW to be unchanged */
    write_byte(TMP105_REG_T_LOW);
    snd_lo_limit = read_word();
    assert_cmpint(lo_limit, ==, snd_lo_limit);
}

static void tmp105_handler(void *opaque, int n, int level)
{
    alarm_rang = level > 0 ? true : false;
    assert_cmpint(n, ==, 3);
}

/*
 * Tests "one-shot" trigger private field.
 */
static void test_os_trigger(void)
{
    const TMP105State *tmp105_state = (TMP105State *) i2c_slave;

    /* trigger "one-shot" temperature reading while in shutdown mode */
    const uint8_t os_config = (1u << 7) | (1u << 0);
    const uint8_t data[] = {TMP105_REG_CONFIG, os_config};

    /* select configuration register */
    write_byte(TMP105_REG_CONFIG);

    /* overwrite configuration register */
    write(data, 2);

    assert(tmp105_state->os_trigger);
    write_byte(TMP105_REG_TEMPERATURE);
    assert(tmp105_state->os_trigger);

    read_byte();
    assert(!tmp105_state->os_trigger);
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

    tmp105_reset(i2c_slave);
    test_change_lower_limit();

    tmp105_reset(i2c_slave);
    test_change_higher_limit();

    tmp105_reset(i2c_slave);
    test_os_trigger();

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
