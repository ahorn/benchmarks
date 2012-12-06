#ifndef QEMU_I2C_H
#define QEMU_I2C_H

/* The QEMU I2C implementation only supports simple transfers that complete
   immediately.  It does not support slave devices that need to be able to
   defer their response (eg. CPU slave interfaces where the data is supplied
   by the device driver in response to an interrupt).  */

enum i2c_event {
    I2C_START_RECV,
    I2C_START_SEND,
    I2C_FINISH,
    I2C_NACK /* Masker NACKed a receive byte.  */
};

typedef struct I2CSlave I2CSlave;

struct I2CSlave {};

/* ... */

#endif
