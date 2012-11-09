/* Copyright (C) 1991-2003,2006,2009,2011 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/*
 *	ISO C99 Standard: 7.23 Date and time	<time.h>
 */

#ifndef	_TIME_H
#define _TIME_H	1

#include <linux/time.h>
#if 0
#ifndef _CLOCK_T
#define _CLOCK_T
  typedef long clock_t; // Just easier to define it here (celina)
#endif

#ifndef _TIME_T
#define _TIME_T
  typedef long time_t; // Just easier to define it here (celina)
#endif
#endif
/* Time used by the program so far (user time + system time).
   The result / CLOCKS_PER_SECOND is program time in seconds.  */
extern clock_t clock (void);

/* Return the current time and put it in *TIMER if TIMER is not NULL.  */
extern time_t time (time_t *__timer);

/* Return the `struct tm' representation of *TIMER
   in Universal Coordinated Time (aka Greenwich Mean Time).  */
extern struct tm *gmtime (__const time_t *__timer);

/* Return the `struct tm' representation
   of *TIMER in the local timezone.  */
extern struct tm *localtime (__const time_t *__timer);

/* Return the `struct tm' representation of *TIMER in UTC,
   using *TP to store the result.  */
extern struct tm *gmtime_r (__const time_t *__restrict __timer,
			    struct tm *__restrict __tp);

/* Return the `struct tm' representation of *TIMER in local time,
   using *TP to store the result.  */
extern struct tm *localtime_r (__const time_t *__restrict __timer,
			       struct tm *__restrict __tp);


#endif /* <time.h> not already included.  */

#ifndef _SYS_TIME_H
#define _SYS_TIME_H	1

/* Get the current time of day and timezone information,
   putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
   Returns 0 on success, -1 on errors.
   NOTE: This form of timezone information is obsolete.
   Use the functions and variables declared in <time.h> instead.  */
extern int clock_gettime(clockid_t clk_id, struct timespec *tp);

extern int gettimeofday(struct timeval *restrict tp, void *restrict tzp);

#endif /* sys/time.h */
