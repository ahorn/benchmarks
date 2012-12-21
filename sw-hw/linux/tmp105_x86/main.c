#include <generated/autoconf.h>
#ifndef _CBMC_
    #include<assert.h>
#endif


/* Linux files */
#include <linux/i2c.h>
//#include <>
/* We include it here because we want to propagate the autoconf */
#include <hwmon/lm75.c>     /* Implements tmp105 driver (lm75 like) */
#include <linux/hwmon-sysfs.h>

#include <kstrtox.c> // kstrstoll
#include <base/dd.c> // i2c_get_clientdata
//#include <base/driver.c> - conflict with rtc-cmos

/* QEMU Model */
#include <tmp105/i2c.h>
#include <tmp105/irq.h>
#include <tmp105/irq.c>
#include <tmp105/tmp105.h>
#include <tmp105/tmp105.c>

/* Interface */
#include "interface.c"

/* PC cmos mappings */

#define REG_EQUIPMENT_BYTE          0x14

#include <stdint.h>

static ssize_t show_temp(struct device *dev, struct device_attribute *da,
			 char *buf);
static ssize_t set_temp(struct device *dev, struct device_attribute *da,
			const char *buf, size_t count);
static int lm75_suspend(struct device *dev);

int nondet_int();

// TODO:
// Replace: kstrtol (might easily blow up)
//            
//            

int main (int argc, char** argv) {

    struct i2c_client client;
    reset_dev(); 

    lm75_driver_init();

    // TODO: Create device
    // Create sensor_device_attribute
    struct sensor_device_attribute sda;
    struct i2c_board_info info;

    int error = lm75_detect (&client, &info);
    int previous = 0;
    char buf [6];

    while (nondet_int()) {
        // TODO: We can split this into many different tests
        // Implement 
        switch (nondet_int()) {
            case 0:
                show_temp ((struct device*) &client,
                           (struct device_attribute *) &sda, buf);
                break;
            case 1:
                // Count (4th parameter) is not used
                set_temp ((struct device*) &client,
                          (struct device_attribute *) &sda, buf, 5);
                break;
            case 2:
                lm75_suspend((struct device*) &client);
                break;
            //case 3:
                //lm75_probe();
                //break;
            default:
                lm75_resume();
                break;
        }
    }

    lm75_driver_exit();

    return 0;
}
