/*
 * QEMU MC146818 RTC emulation
 *
 * Copyright (c) 2003-2004 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "mc146818rtc.h"
#include "qemu-timer.h"
#include "qverify.h"
//#include "rtc-verify.h"

#ifdef _CBMC_
  #include <linux/string.h>
#elif defined(_KLEE_)
  #include <assert.h>
#else
  #include <string.h>
  // conflict with Linux kernel header when running CBMC
  #include <assert.h>
#endif

#ifdef DEBUG_CMOS
# define CMOS_DPRINTF(format, ...)   printf(format, ## __VA_ARGS__)
#else
# define CMOS_DPRINTF(format, ...)   do { } while (0)
#endif

#ifdef DEBUG_COALESCED
# define DPRINTF_C(format, ...)      printf(format, ## __VA_ARGS__)
#else
# define DPRINTF_C(format, ...)      do { } while (0)
#endif

#ifndef _CBMC_
  #define NSEC_PER_SEC    1000000000LL
#endif

#define SEC_PER_MIN     60
#define MIN_PER_HOUR    60
#define SEC_PER_HOUR    3600
#define HOUR_PER_DAY    24
#define SEC_PER_DAY     86400

#define RTC_REINJECT_ON_ACK_COUNT 20
#define RTC_CLOCK_RATE            32768
#define UIP_HOLD_LENGTH           (8 * NSEC_PER_SEC / 32768)

#define OUTB_0x70       1
#define OUTB_0x71       2
#define INB_0x70        3
#define INB_0x71        4

struct IRQState {};
typedef struct IRQState *qemu_irq;
static void qemu_irq_raise(qemu_irq irq) {}
static inline void qemu_irq_lower(qemu_irq irq) {}

struct RTCState {
    uint8_t cmos_data[128];

    /* The century byte is excluded because
     * it is not described in the data sheet. */
    uint8_t cmos_data_copy[10];
    bool cmos_data_copy_check;
    uint8_t cmos_index;
    int32_t base_year;
    uint64_t base_rtc;
    uint64_t last_update;
    int64_t offset;
    qemu_irq irq;
    qemu_irq sqw_irq;
    int it_shift;
    /* periodic timer */
    QEMUTimer *periodic_timer;
    int64_t next_periodic_time;
    /* update-ended timer */
    QEMUTimer *update_timer;
    uint64_t next_alarm_time;
    uint16_t irq_reinject_on_ack_count;
    uint32_t irq_coalesced;
    uint32_t period;

    /* == meta-data == */

    /* most recent I/O op */
    uint32_t io_info;
    /* Which data register has been written? */
    bool cmos_data_info[128];
    /* Has DM bit of Register B changed? */
    bool dm_change;
};

static RTCState global_rtc_state;

static void _rtc_set_time(RTCState *s);
static void _rtc_update_time(RTCState *s);
static void _rtc_set_cmos(RTCState *s, const struct tm *tm);
static inline int _rtc_from_bcd(RTCState *s, int a);
static uint64_t get_next_alarm(RTCState *s);

static time_t mktimegm(struct tm *tm)
{
    time_t t;
    int y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;
    if (m < 3) {
        m += 12;
        y--;
    }
    t = 86400ULL * (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + 
                 y / 400 - 719469);
    t += 3600 * tm->tm_hour + 60 * tm->tm_min + tm->tm_sec;
    return t;
}

static inline bool _rtc_running(RTCState *s)
{
    return (!(s->cmos_data[RTC_REG_B] & REG_B_SET) &&
            (s->cmos_data[RTC_REG_A] & 0x70) <= 0x20);
}

static uint64_t get_guest_rtc_ns(RTCState *s)
{
    uint64_t guest_rtc;
    uint64_t guest_clock = qemu_get_clock_ns(rtc_clock);

    guest_rtc = s->base_rtc * NSEC_PER_SEC
                 + guest_clock - s->last_update + s->offset;
    return guest_rtc;
}

/* compute with 96 bit intermediate result: (a*b)/c */
static inline uint64_t muldiv64(uint64_t a, uint32_t b, uint32_t c)
{
    union {
        uint64_t ll;
        struct {
#ifdef HOST_WORDS_BIGENDIAN
            uint32_t high, low;
#else
            uint32_t low, high;
#endif
        } l;
    } u, res;
    uint64_t rl, rh;

    u.ll = a;
    rl = (uint64_t)u.l.low * (uint64_t)b;
    rh = (uint64_t)u.l.high * (uint64_t)b;
    rh += (rl >> 32);
    res.l.high = rh / c;
    res.l.low = (((rh % c) << 32) + (rl & 0xffffffff)) / c;
    return res.ll;
}

/* handle periodic timer */
static void periodic_timer_update(RTCState *s, int64_t current_time)
{
    int period_code, period;
    int64_t cur_clock, next_irq_clock;

    period_code = s->cmos_data[RTC_REG_A] & 0x0f;
    if (period_code != 0
        && ((s->cmos_data[RTC_REG_B] & REG_B_PIE)
            || ((s->cmos_data[RTC_REG_B] & REG_B_SQWE) && s->sqw_irq))) {
        if (period_code <= 2)
            period_code += 7;
        /* period in 32 Khz cycles */
        period = 1 << (period_code - 1);
        /* compute 32 khz clock */
        cur_clock = muldiv64(current_time, RTC_CLOCK_RATE, get_ticks_per_sec());
        next_irq_clock = (cur_clock & ~(period - 1)) + period;
        s->next_periodic_time =
            muldiv64(next_irq_clock, get_ticks_per_sec(), RTC_CLOCK_RATE) + 1;
        qemu_mod_timer(s->periodic_timer, s->next_periodic_time);
    } else {
        qemu_del_timer(s->periodic_timer);
    }
}

static void _rtc_periodic_timer(void *opaque)
{
    RTCState *s = opaque;

    periodic_timer_update(s, s->next_periodic_time);
    s->cmos_data[RTC_REG_C] |= REG_C_PF;
    if (s->cmos_data[RTC_REG_B] & REG_B_PIE) {
        s->cmos_data[RTC_REG_C] |= REG_C_IRQF;
        qemu_irq_raise(s->irq);
    }
    if (s->cmos_data[RTC_REG_B] & REG_B_SQWE) {
        /* Not square wave at all but we don't want 2048Hz interrupts!
           Must be seen as a pulse.  */
        qemu_irq_raise(s->sqw_irq);
    }
}

/* handle update-ended timer */
static void check_update_timer(RTCState *s)
{
    uint64_t next_update_time;
    uint64_t guest_nsec;
    int next_alarm_sec;

    /* From the data sheet: "Holding the dividers in reset prevents
     * interrupts from operating, while setting the SET bit allows"
     * them to occur.  However, it will prevent an alarm interrupt
     * from occurring, because the time of day is not updated.
     */
#ifndef __NO_TIMER__
    if ((s->cmos_data[RTC_REG_A] & 0x60) == 0x60) {
        qemu_del_timer(s->update_timer);
        return;
    }
    if ((s->cmos_data[RTC_REG_C] & REG_C_UF) &&
        (s->cmos_data[RTC_REG_B] & REG_B_SET)) {
        qemu_del_timer(s->update_timer);
        return;
    }
    if ((s->cmos_data[RTC_REG_C] & REG_C_UF) &&
        (s->cmos_data[RTC_REG_C] & REG_C_AF)) {
        qemu_del_timer(s->update_timer);
        return;
    }
#endif
    guest_nsec = get_guest_rtc_ns(s) % NSEC_PER_SEC;
    /* if UF is clear, reprogram to next second */
    next_update_time = qemu_get_clock_ns(rtc_clock)
        + NSEC_PER_SEC - guest_nsec;

    /* Compute time of next alarm.  One second is already accounted
     * for in next_update_time.
     */
    next_alarm_sec = get_next_alarm(s);
    s->next_alarm_time = next_update_time + (next_alarm_sec - 1) * NSEC_PER_SEC;

    if (s->cmos_data[RTC_REG_C] & REG_C_UF) {
        /* UF is set, but AF is clear.  Program the timer to target
         * the alarm time.  */
        next_update_time = s->next_alarm_time;
    }
#ifndef __NO_TIMER__
    if (next_update_time != qemu_timer_expire_time_ns(s->update_timer)) {
        qemu_mod_timer(s->update_timer, next_update_time);
    }
#endif
}

static inline uint8_t convert_hour(RTCState *s, uint8_t hour)
{
    if (!(s->cmos_data[RTC_REG_B] & REG_B_24H)) {
        hour %= 12;
        if (s->cmos_data[RTC_HOURS] & 0x80) {
            hour += 12;
        }
    }
    return hour;
}

static uint64_t get_next_alarm(RTCState *s)
{
    int32_t alarm_sec, alarm_min, alarm_hour, cur_hour, cur_min, cur_sec;
    int32_t hour, min, sec;

    _rtc_update_time(s);

    alarm_sec = _rtc_from_bcd(s, s->cmos_data[RTC_SECONDS_ALARM]);
    alarm_min = _rtc_from_bcd(s, s->cmos_data[RTC_MINUTES_ALARM]);
    alarm_hour = _rtc_from_bcd(s, s->cmos_data[RTC_HOURS_ALARM]);
    alarm_hour = alarm_hour == -1 ? -1 : convert_hour(s, alarm_hour);

    cur_sec = _rtc_from_bcd(s, s->cmos_data[RTC_SECONDS]);
    cur_min = _rtc_from_bcd(s, s->cmos_data[RTC_MINUTES]);
    cur_hour = _rtc_from_bcd(s, s->cmos_data[RTC_HOURS]);
    cur_hour = convert_hour(s, cur_hour);

    if (alarm_hour == -1) {
        alarm_hour = cur_hour;
        if (alarm_min == -1) {
            alarm_min = cur_min;
            if (alarm_sec == -1) {
                alarm_sec = cur_sec + 1;
            } else if (cur_sec > alarm_sec) {
                alarm_min++;
            }
        } else if (cur_min == alarm_min) {
            if (alarm_sec == -1) {
                alarm_sec = cur_sec + 1;
            } else {
                if (cur_sec > alarm_sec) {
                    alarm_hour++;
                }
            }
            if (alarm_sec == SEC_PER_MIN) {
                /* wrap to next hour, minutes is not in don't care mode */
                alarm_sec = 0;
                alarm_hour++;
            }
        } else if (cur_min > alarm_min) {
            alarm_hour++;
        }
    } else if (cur_hour == alarm_hour) {
        if (alarm_min == -1) {
            alarm_min = cur_min;
            if (alarm_sec == -1) {
                alarm_sec = cur_sec + 1;
            } else if (cur_sec > alarm_sec) {
                alarm_min++;
            }

            if (alarm_sec == SEC_PER_MIN) {
                alarm_sec = 0;
                alarm_min++;
            }
            /* wrap to next day, hour is not in don't care mode */
            alarm_min %= MIN_PER_HOUR;
        } else if (cur_min == alarm_min) {
            if (alarm_sec == -1) {
                alarm_sec = cur_sec + 1;
            }
            /* wrap to next day, hours+minutes not in don't care mode */
            alarm_sec %= SEC_PER_MIN;
        }
    }

    /* values that are still don't care fire at the next min/sec */
    if (alarm_min == -1) {
        alarm_min = 0;
    }
    if (alarm_sec == -1) {
        alarm_sec = 0;
    }

    /* keep values in range */
    if (alarm_sec == SEC_PER_MIN) {
        alarm_sec = 0;
        alarm_min++;
    }
    if (alarm_min == MIN_PER_HOUR) {
        alarm_min = 0;
        alarm_hour++;
    }
    alarm_hour %= HOUR_PER_DAY;

    hour = alarm_hour - cur_hour;
    min = hour * MIN_PER_HOUR + alarm_min - cur_min;
    sec = min * SEC_PER_MIN + alarm_sec - cur_sec;
    return sec <= 0 ? sec + SEC_PER_DAY : sec;
}

static void _rtc_update_timer(void *opaque)
{
    RTCState *s = opaque;
    int32_t irqs = REG_C_UF;
    int32_t new_irqs;

    assert((s->cmos_data[RTC_REG_A] & 0x60) != 0x60);

    /* UIP might have been latched, update time and clear it.  */
    _rtc_update_time(s);
    s->cmos_data[RTC_REG_A] &= ~REG_A_UIP;

    if (qemu_get_clock_ns(rtc_clock) >= s->next_alarm_time) {
        irqs |= REG_C_AF;
        if (s->cmos_data[RTC_REG_B] & REG_B_AIE) {
            //qemu_system_wakeup_request(QEMU_WAKEUP_REASON_RTC);
        }
    }

    new_irqs = irqs & ~s->cmos_data[RTC_REG_C];
    s->cmos_data[RTC_REG_C] |= irqs;
    if ((new_irqs & s->cmos_data[RTC_REG_B]) != 0) {
        s->cmos_data[RTC_REG_C] |= REG_C_IRQF;
        qemu_irq_raise(s->irq);
    }
    check_update_timer(s);
}

/* Copy content of RTC data registers for verification purposes */
static void copy_data(RTCState *s) {
    s->cmos_data_copy_check = (s->cmos_data[RTC_REG_B] & REG_B_SET) == REG_B_SET;

    uint32_t rtc_data_addr;
    for(rtc_data_addr = RTC_SECONDS;
        rtc_data_addr <= RTC_YEAR;
        rtc_data_addr++) {

        s->cmos_data_copy[rtc_data_addr] = s->cmos_data[rtc_data_addr];
    }
}

/* If the SET bit of Register B was enabled when the RTC data registers
 * were copied and the SET bit is now still enabled, then assert that the
 * content of the ten RTC data registers has not changed.
 *
 * This function together with copy_data() can be used to check the VC:
 *
 *     As long as the SET bit of Register B is enabled, when data D
 *     is written to an RTC data register R, a subsequent read of R
 *     must return D.
 */
static void assert_equal_copy_data(RTCState *s) {
    if (s->cmos_data_copy_check &&
         ((s->cmos_data[RTC_REG_B] & REG_B_SET) == REG_B_SET)) {

        uint32_t rtc_data_addr;
        for(rtc_data_addr = RTC_SECONDS;
            rtc_data_addr <= RTC_YEAR;
            rtc_data_addr++) {

            assert(s->cmos_data_copy[rtc_data_addr] == s->cmos_data[rtc_data_addr]);
        }
    }
}

void cmos_ioport_write(void *opaque, uint32_t addr, uint32_t data)
{
    RTCState *s = opaque;

    if ((addr & 1) == 0) {
        s->io_info = OUTB_0x70;
        s->cmos_index = data & 0x7f;
    } else {
        #if (defined RTC_BENCHMARK_PROP_1 || defined RTC_BENCHMARK_PROP_2)
	    copy_data(s);
	#endif
        /* VC: outb 0x71 must be preceded by outb 0x70 */
#ifdef RTC_BENCHMARK_PROP_8
        assert(s->io_info == OUTB_0x70);
#endif
        s->io_info = OUTB_0x71;

        CMOS_DPRINTF("cmos: write index=0x%02x val=0x%02x\n",
                     s->cmos_index, data);
        switch(s->cmos_index) {
        case RTC_SECONDS_ALARM:
        case RTC_MINUTES_ALARM:
        case RTC_HOURS_ALARM:
            s->cmos_data_info[s->cmos_index] = true;

            /* VC: SET bit of Register B must be enabled
             *     when an RTC data register is written */
#ifdef RTC_BENCHMARK_PROP_9
            assert((s->cmos_data[RTC_REG_B] & REG_B_SET) == REG_B_SET);
#endif

            s->cmos_data[s->cmos_index] = data;
            check_update_timer(s);
            break;
	case RTC_IBM_PS2_CENTURY_BYTE:
            s->cmos_index = RTC_CENTURY;
            /* fall through */
        case RTC_CENTURY:
        case RTC_SECONDS:
        case RTC_MINUTES:
        case RTC_HOURS:
        case RTC_DAY_OF_WEEK:
        case RTC_DAY_OF_MONTH:
        case RTC_MONTH:
        case RTC_YEAR:
            s->cmos_data_info[s->cmos_index] = true;

            /* VC: SET bit of Register B must be enabled
             *     when an RTC data register is written */
#ifdef RTC_BENCHMARK_PROP_10
            assert((s->cmos_data[RTC_REG_B] & REG_B_SET) == REG_B_SET);
#endif

            s->cmos_data[s->cmos_index] = data;
            /* if in set mode, do not update the time */
            if (_rtc_running(s)) {
                _rtc_set_time(s);
                check_update_timer(s);
            }

            /* VC: As long as the SET bit of Register B is enabled, when data D
             *     is written to an RTC data register R, a subsequent read of R
             *     must return D. */
#ifdef RTC_BENCHMARK_PROP_11
            assert((s->cmos_data[RTC_REG_B] & REG_B_SET) == 0 ||
                   s->cmos_data[s->cmos_index] == data);
#endif
            break;
        case RTC_REG_A:
            if ((data & 0x60) == 0x60) {
                if (_rtc_running(s)) {
                    _rtc_update_time(s);
                }
                /* What happens to UIP when divider reset is enabled is
                 * unclear from the datasheet.  Shouldn't matter much
                 * though.
                 */
                s->cmos_data[RTC_REG_A] &= ~REG_A_UIP;
            } else if (((s->cmos_data[RTC_REG_A] & 0x60) == 0x60) &&
                    (data & 0x70)  <= 0x20) {
                /* when the divider reset is removed, the first update cycle
                 * begins one-half second later*/
                if (!(s->cmos_data[RTC_REG_B] & REG_B_SET)) {
                    s->offset = 500000000;
                    _rtc_set_time(s);
                }
                s->cmos_data[RTC_REG_A] &= ~REG_A_UIP;
            }
            /* UIP bit is read only */
            s->cmos_data[RTC_REG_A] = (data & ~REG_A_UIP) |
                (s->cmos_data[RTC_REG_A] & REG_A_UIP);
#ifndef __NO_TIMER__    
	    periodic_timer_update(s, qemu_get_clock_ns(rtc_clock));
#endif
	    check_update_timer(s);

#ifdef RTC_BENCHMARK_PROP_1
            assert_equal_copy_data(s);
#endif
            break;
        case RTC_REG_B:
            /* Is DM bit of Register B being changed? */
            if ((s->cmos_data[RTC_REG_B] & REG_B_DM) != ((uint8_t) data & REG_B_DM)) {
#ifdef RTC_BENCHMARK_PROP_3
                /* VC: If DM bit of Register B is being changed,
                 *     then either the SET bit of Register B has been
                 *     enabled or is being simultaneously enabled. */
                assert((data & REG_B_SET) == REG_B_SET ||
                       (s->cmos_data[RTC_REG_B] & REG_B_SET) == REG_B_SET);
#endif
                s->dm_change = true;
            }

            if (data & REG_B_SET) {
                /* update cmos to when the rtc was stopping */
                if (_rtc_running(s)) {
                    _rtc_update_time(s);
                }
                /* set mode: reset UIP mode */
                s->cmos_data[RTC_REG_A] &= ~REG_A_UIP;
                data &= ~REG_B_UIE;
            } else {
                /* if disabling set mode, update the time */
                if ((s->cmos_data[RTC_REG_B] & REG_B_SET) &&
                    (s->cmos_data[RTC_REG_A] & 0x70) <= 0x20) {
                    s->offset = get_guest_rtc_ns(s) % NSEC_PER_SEC;
                    _rtc_set_time(s);
                }
            }
            /* if an interrupt flag is already set when the interrupt
             * becomes enabled, raise an interrupt immediately.  */
            if (data & s->cmos_data[RTC_REG_C] & REG_C_MASK) {
                s->cmos_data[RTC_REG_C] |= REG_C_IRQF;
                qemu_irq_raise(s->irq);
            } else {
                s->cmos_data[RTC_REG_C] &= ~REG_C_IRQF;
                qemu_irq_lower(s->irq);
            }

            s->cmos_data[RTC_REG_B] = data;
#ifndef __NO_TIMER__
            periodic_timer_update(s, qemu_get_clock_ns(rtc_clock));
#endif
	    check_update_timer(s);

            /* VC: In Register B, if its SET bit is being disabled and its
             *     DM bit has changed since the SET bit has been enabled,
             *     then every RTC data register must have been written.
             *
             *     In other words, a change of the DM bit in Register B must
             *     be either followed or preceded by writes to every RTC data
             *     register before the SET bit of Register B is disabled.
             *
             *     This VC intends to permit that the SET and DM bit of
             *     Register B are being enabled simultaneously. In addition,
             *     the intention is to allow the DM bit to being enabled
             *     while the SET bit is simultaneously disabled provided
             *     that all RTC data registers have been written. */
            if (s->dm_change && (data & REG_B_SET) == 0) {
                uint32_t rtc_data_addr;
 #ifdef RTC_BENCHMARK_PROP_4
                assert(s->cmos_data_info[RTC_CENTURY]);
                for(rtc_data_addr = RTC_SECONDS;
                    rtc_data_addr <= RTC_YEAR;
                    rtc_data_addr++) {

                    assert(s->cmos_data_info[rtc_data_addr]);
                }
#endif

                /* reset meta-data */
                s->dm_change = false;
                s->cmos_data_info[RTC_CENTURY] = false;
                for(rtc_data_addr = RTC_SECONDS;
                    rtc_data_addr <= RTC_YEAR;
                    rtc_data_addr++) {

                    s->cmos_data_info[rtc_data_addr] = false;
                }
            }

#ifdef RTC_BENCHMARK_PROP_2
            assert_equal_copy_data(s);
#endif
            break;
        default:
            /* VC: Only registers 0x00 to 0x0D must be accessed. */
            /* VC: Registers C and D must not be written. */
#ifdef RTC_BENCHMARK_PROP_5
            assert(false);
#endif
            break;
        }
    }
}

static inline int _rtc_to_bcd(RTCState *s, int a)
{
    if (s->cmos_data[RTC_REG_B] & REG_B_DM) {
        return a;
    } else {
        return ((a / 10) << 4) | (a % 10);
    }
}

static inline int _rtc_from_bcd(RTCState *s, int a)
{
    if ((a & 0xc0) == 0xc0) {
        return -1;
    }
    if (s->cmos_data[RTC_REG_B] & REG_B_DM) {
        return a;
    } else {
        return ((a >> 4) * 10) + (a & 0x0f);
    }
}

static void _rtc_get_time(RTCState *s, struct tm *tm)
{
    tm->tm_sec = _rtc_from_bcd(s, s->cmos_data[RTC_SECONDS]);
    tm->tm_min = _rtc_from_bcd(s, s->cmos_data[RTC_MINUTES]);
    tm->tm_hour = _rtc_from_bcd(s, s->cmos_data[RTC_HOURS] & 0x7f);
    if (!(s->cmos_data[RTC_REG_B] & REG_B_24H)) {
        tm->tm_hour %= 12;
        if (s->cmos_data[RTC_HOURS] & 0x80) {
            tm->tm_hour += 12;
        }
    }
    tm->tm_wday = _rtc_from_bcd(s, s->cmos_data[RTC_DAY_OF_WEEK]) - 1;
    tm->tm_mday = _rtc_from_bcd(s, s->cmos_data[RTC_DAY_OF_MONTH]);
    tm->tm_mon = _rtc_from_bcd(s, s->cmos_data[RTC_MONTH]) - 1;
    tm->tm_year =
        _rtc_from_bcd(s, s->cmos_data[RTC_YEAR]) + s->base_year +
        _rtc_from_bcd(s, s->cmos_data[RTC_CENTURY]) * 100 - 1900;
}

static void _rtc_set_time(RTCState *s)
{
    struct tm tm;

    _rtc_get_time(s, &tm);
    s->base_rtc = mktimegm(&tm);
    s->last_update = qemu_get_clock_ns(rtc_clock);
}

static void _rtc_set_cmos(RTCState *s, const struct tm *tm)
{
    int year;

    s->cmos_data[RTC_SECONDS] = _rtc_to_bcd(s, tm->tm_sec);
    s->cmos_data[RTC_MINUTES] = _rtc_to_bcd(s, tm->tm_min);
    if (s->cmos_data[RTC_REG_B] & REG_B_24H) {
        /* 24 hour format */
        s->cmos_data[RTC_HOURS] = _rtc_to_bcd(s, tm->tm_hour);
    } else {
        /* 12 hour format */
        int h = (tm->tm_hour % 12) ? tm->tm_hour % 12 : 12;
        s->cmos_data[RTC_HOURS] = _rtc_to_bcd(s, h);
        if (tm->tm_hour >= 12)
            s->cmos_data[RTC_HOURS] |= 0x80;
    }
    s->cmos_data[RTC_DAY_OF_WEEK] = _rtc_to_bcd(s, tm->tm_wday + 1);
    s->cmos_data[RTC_DAY_OF_MONTH] = _rtc_to_bcd(s, tm->tm_mday);
    s->cmos_data[RTC_MONTH] = _rtc_to_bcd(s, tm->tm_mon + 1);
    year = tm->tm_year + 1900 - s->base_year;
    s->cmos_data[RTC_YEAR] = _rtc_to_bcd(s, year % 100);
    s->cmos_data[RTC_CENTURY] = _rtc_to_bcd(s, year / 100);
}

static void _rtc_update_time(RTCState *s)
{
    struct tm ret;
    time_t guest_sec;
    int64_t guest_nsec;

    guest_nsec = get_guest_rtc_ns(s);
    guest_sec = guest_nsec / NSEC_PER_SEC;
    gmtime_r(&guest_sec, &ret);

#ifdef __EXPOSE_BUG__
        _rtc_set_cmos(s, &ret);
#else
    /* Fixes bug:
     *    http://git.qemu.org/?p=qemu.git;a=commit;h=02c6ccc6dde90dcbf5975b1cfe2ab199e525ec11
     */
    if ((s->cmos_data[RTC_REG_B] & REG_B_SET) == 0) {
        _rtc_set_cmos(s, &ret);
    }
#endif
}

static int update_in_progress(RTCState *s)
{
    int64_t guest_nsec;

    if (!_rtc_running(s)) {
        return 0;
    }
#ifndef __NO_TIMER__
    if (qemu_timer_pending(s->update_timer)) {
        int64_t next_update_time = qemu_timer_expire_time_ns(s->update_timer);
        /* Latch UIP until the timer expires.  */
        if (qemu_get_clock_ns(rtc_clock) >= (next_update_time - UIP_HOLD_LENGTH)) {
            s->cmos_data[RTC_REG_A] |= REG_A_UIP;
            return 1;
        }
    }
#else
    int nondet_flag;
    if (nondet_flag) {
	s->cmos_data[RTC_REG_A] |= REG_A_UIP;
	return 1;
    }
#endif
    guest_nsec = get_guest_rtc_ns(s);
    /* UIP bit will be set at last 244us of every second. */
    if ((guest_nsec % NSEC_PER_SEC) >= (NSEC_PER_SEC - UIP_HOLD_LENGTH)) {
        return 1;
    }
    return 0;
}

uint32_t cmos_ioport_read(void *opaque, uint32_t addr)
{
    RTCState *s = opaque;
    int ret;
    if ((addr & 1) == 0) {
        s->io_info = INB_0x70;
        return 0xff;
    } else {
        /* VC: inb 0x71 must be preceded by outb 0x70 */
#ifdef RTC_BENCHMARK_PROP_6
        assert(s->io_info == OUTB_0x70);
#endif
        s->io_info = INB_0x71;

        switch(s->cmos_index) {
	case RTC_IBM_PS2_CENTURY_BYTE:
            s->cmos_index = RTC_CENTURY;
            /* fall through */
        case RTC_CENTURY:
        case RTC_SECONDS:
        case RTC_MINUTES:
        case RTC_HOURS:
        case RTC_DAY_OF_WEEK:
        case RTC_DAY_OF_MONTH:
        case RTC_MONTH:
        case RTC_YEAR:
            /* if not in set mode, calibrate cmos before
             * reading*/
            if (_rtc_running(s)) {
                _rtc_update_time(s);
            }

            ret = s->cmos_data[s->cmos_index];
            break;
        case RTC_REG_A:
            if (update_in_progress(s)) {
                s->cmos_data[s->cmos_index] |= REG_A_UIP;
            } else {
                s->cmos_data[s->cmos_index] &= ~REG_A_UIP;
            }
            ret = s->cmos_data[s->cmos_index];
            break;
        case RTC_REG_C:
            ret = s->cmos_data[s->cmos_index];
            qemu_irq_lower(s->irq);
            s->cmos_data[RTC_REG_C] = 0x00;
            if (ret & (REG_C_UF | REG_C_AF)) {
                check_update_timer(s);
            }
            break;
        case RTC_SECONDS_ALARM:
        case RTC_MINUTES_ALARM:
        case RTC_HOURS_ALARM:
        case RTC_REG_B:
        case RTC_REG_D:
            ret = s->cmos_data[s->cmos_index];
            break;
        default:
            /* VC: Only registers 0x00 to 0x0D must be accessed. */
#ifdef RTC_BENCHMARK_PROP_7
            assert(false);
#endif
            break;
        }
        CMOS_DPRINTF("cmos: read index=0x%02x val=0x%02x\n",
                     s->cmos_index, ret);
        return ret;
    }
}

void _rtc_set_memory(RTCState *s, int addr, int val)
{
    if (addr >= 0 && addr <= 127)
        s->cmos_data[addr] = val;
}

static int _rtc_date_offset = -1; /* -1 means no change */
static int _rtc_utc = 1; /* make non-determinstic */


static void qemu_get_timedate(struct tm *tm, int offset)
{
    time_t ti;

    time(&ti);
    ti += offset;
    if (_rtc_date_offset == -1) {
        if (_rtc_utc)
            tm = gmtime(&ti);
        else
            tm = localtime(&ti);
    } else {
        ti -= _rtc_date_offset;
        tm = gmtime(&ti);
    }
}

static void _rtc_set_date_from_host(RTCState *s)
{
    struct tm tm;

    qemu_get_timedate(&tm, 0);

    s->base_rtc = mktimegm(&tm);
    s->last_update = qemu_get_clock_ns(rtc_clock);
    s->offset = 0;

    /* set the CMOS date */
    _rtc_set_cmos(s, &tm);
}

void _rtc_reset(RTCState *s)
{

    s->cmos_data[RTC_REG_B] &= ~(REG_B_PIE | REG_B_AIE | REG_B_SQWE);
    s->cmos_data[RTC_REG_C] &= ~(REG_C_UF | REG_C_IRQF | REG_C_PF | REG_C_AF);
    check_update_timer(s);

    qemu_irq_lower(s->irq);
}


static int _rtc_initfn(RTCState *s)
{
    s->cmos_data[RTC_REG_A] = 0x26;
    s->cmos_data[RTC_REG_B] = 0x02;
    s->cmos_data[RTC_REG_C] = 0x00;
    s->cmos_data[RTC_REG_D] = 0x80;

    /* This is for historical reasons.  The default base year qdev property
     * was set to 2000 for most machine types before the century byte was
     * implemented.
     *
     * This if statement means that the century byte will be always 0
     * (at least until 2079...) for base_year = 1980, but will be set
     * correctly for base_year = 2000.
     */
    if (s->base_year == 2000) {
        s->base_year = 0;
    }

    _rtc_set_date_from_host(s);

    static QEMUTimer _periodic_timer = { .expire_time = 0,
                                         .next = NULL,
                                         .scale = SCALE_NS };

    _periodic_timer.clock = rtc_clock;
    _periodic_timer.cb = _rtc_periodic_timer;
    _periodic_timer.opaque = s;


    s->periodic_timer = &_periodic_timer;

    static QEMUTimer _update_timer = { .expire_time = 0,
                                       .next = NULL,
                                       .scale = SCALE_NS };

    _update_timer.clock = rtc_clock;
    _update_timer.cb = _rtc_update_timer;
    _update_timer.opaque = s;

    s->update_timer = &_update_timer;
    check_update_timer(s);

    s->io_info = -1;

    return 0;
}

void _rtc_init(int base_year)
{
    RTCState *s;

    s = &global_rtc_state;
    set_global_qverify_rtc_state(s);

    s->base_year = base_year;
    _rtc_initfn(s);
}

