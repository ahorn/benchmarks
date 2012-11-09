#ifndef QEMU_TIMER_H
#define QEMU_TIMER_H
  

#if defined (_CBMC_) || defined (_SYS_)
  #include <time.h>
  #include <linux/time.h>
  #include <stdint.h> // modlib
#else
  #include <stdint.h>
  #include <stdbool.h>
  #include <sys/time.h>
#endif

#define SCALE_MS 1000000
#define SCALE_US 1000
#define SCALE_NS 1

typedef struct QEMUTimer QEMUTimer;
typedef struct QEMUClock QEMUClock;
typedef void QEMUTimerCB(void *opaque);

extern QEMUClock *rtc_clock;

/* timers */

/* The real time clock should be used only for stuff which does not
   change the virtual machine state, as it is run even if the virtual
   machine is stopped. The real time clock has a frequency of 1000
   Hz. */
extern QEMUClock *rt_clock;

/* The virtual clock is only run during the emulation. It is stopped
   when the virtual machine is stopped. Virtual timers use a high
   precision clock, usually cpu cycles (use ticks_per_sec). */
extern QEMUClock *vm_clock;

/* The host clock should be use for device models that emulate accurate
   real time sources. It will continue to run when the virtual machine
   is suspended, and it will reflect system time changes the host may
   undergo (e.g. due to NTP). The host clock has the same precision as
   the virtual clock. */
extern QEMUClock *host_clock;

struct QEMUClock {
    QEMUTimer *active_timers;
    int64_t last;
    int type;
    bool enabled;
};

struct QEMUTimer {
    int64_t expire_time;	/* in nanoseconds */
    QEMUClock *clock;
    QEMUTimerCB *cb;
    void *opaque;
    QEMUTimer *next;
    int scale;
};

int64_t get_clock(void);
int64_t qemu_get_clock_ns(QEMUClock *clock);
int64_t qemu_clock_has_timers(QEMUClock *clock);
int64_t qemu_clock_expired(QEMUClock *clock);
int64_t qemu_clock_deadline(QEMUClock *clock);
void qemu_clock_warp(QEMUClock *clock);

void qemu_del_timer(QEMUTimer *ts);
void qemu_mod_timer_ns(QEMUTimer *ts, int64_t expire_time);
void qemu_mod_timer(QEMUTimer *ts, int64_t expire_time);
bool qemu_timer_pending(QEMUTimer *ts);
bool qemu_timer_expired(QEMUTimer *timer_head, int64_t current_time);
uint64_t qemu_timer_expire_time_ns(QEMUTimer *ts);

void qemu_run_timers(QEMUClock *clock);
void qemu_run_all_timers(void);

int64_t cpu_get_ticks(void);
void cpu_enable_ticks(void);
void cpu_disable_ticks(void);

static inline int64_t get_ticks_per_sec(void)
{
    return 1000000000LL;
}

/* real time host monotonic timer */
static inline int64_t get_clock_realtime(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000000LL + (tv.tv_usec * 1000);
}

extern int use_rt_clock;

#endif
