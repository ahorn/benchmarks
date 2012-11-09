#ifndef MC146818RTC_H
#define MC146818RTC_H

#if defined (_CBMC_) || defined (_SYS_)
  #include <linux/types.h>
#else
  #include <stdint.h>
#endif

#include "mc146818rtc_regs.h"

typedef struct RTCState RTCState;

uint32_t cmos_ioport_read(void *opaque, uint32_t addr);
void cmos_ioport_write(void *opaque, uint32_t addr, uint32_t data);
void _rtc_init(int base_year);
void _rtc_set_memory(RTCState *s, int addr, int val);
void _rtc_reset(RTCState *s);

#endif
