#include <generated/autoconf.h>
#include <stdint.h>

#ifndef _CBMC_
    #include <assert.h>
#endif

/* Linux files */
#include <linux/i2c.h>
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

/* Interface between software and hardware */
#include "sw-hw.c"

/* PC cmos mappings */
#define REG_EQUIPMENT_BYTE          0x14

// From arch/x86/kernel/time.c
unsigned long volatile jiffies = ((unsigned long)(unsigned int) (-300*HZ));

int nondet_int();

// TODO:
// Replace: kstrtol (might easily blow up)
//            

int main (int argc, char** argv) {

    struct i2c_client client;
    reset_dev(); 

    // Creat device
    lm75_driver_init();

    // Create sensor_device_attribute
    struct sensor_device_attribute sda;
    struct i2c_board_info info;

#ifdef _KLEE_
    klee_make_symbolic(&client, sizeof(client), "client");
    klee_make_symbolic(&sda, sizeof(sda), "sda");
    klee_make_symbolic(&info, sizeof(info), "info");
#endif

    int error = lm75_detect(&client, &info);

#ifdef _CBMC_
     __CPROVER_assume(error == 0);
#elif defined(_KLEE_)
    klee_assume(error == 0);
#else
    assert(!error);
#endif
        
    char buf [6];

#ifdef _KLEE_
    klee_make_symbolic(buf, sizeof(buf), "buf");
    /* force internal integer conversion in kstrtol() to terminate quickly */
    klee_assume(buf[5] == 0); 
#else 
    buf[5] = 0;
#endif

    /* Test cases */
#ifdef _CBMC_
    __CPROVER_assume(sda.index == 1 || sda.index == 2);
#endif
#ifdef _KLEE_
    klee_assume(sda.index == 1 || sda.index == 2);
#endif

    // The length of test sequence 
    int test_seq_len = 15; 
    for (int test_i = 0; test_i < test_seq_len; test_i++) {
        // We can split this into many different tests
#ifndef _KLEE_
        int switch_case = nondet_int();
#endif
#ifdef _CBMC_
	__CPROVER_assume(switch_case >= 0 && switch_case < 5);
#endif
#ifdef _KLEE_
	int switch_case;
	klee_make_symbolic(&switch_case, sizeof(switch_case), "switch_case");
	klee_assume(switch_case >= 0 && switch_case < 5);
#endif
        switch (switch_case) {
            case 0:
                show_temp (&client.dev,
                           &sda.dev_attr, buf);
                break;
            case 1:
                // Count (4th parameter) is not used
                set_temp (&client.dev,
                          &sda.dev_attr, buf, 5);
                break;
            case 2:
                lm75_suspend(&client.dev);
                break;
            case 3:
                lm75_probe(&client, &lm75_ids[12]);
                break;
            default:
                lm75_resume(&client.dev);
                break;
        }
    }
    
    lm75_driver_exit();

    return 0;
}
