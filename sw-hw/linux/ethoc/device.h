/*
 * Simplified device.h - generic, centralized driver model
 *
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Hartman <gregkh@suse.de>
 * Copyright (c) 2008-2009 Novell Inc.
 *
 * This file is released under the GPLv2
 *
 * See Documentation/driver-model/ for more information.
 */

#ifndef _DEVICE_H_
#define _DEVICE_H_

/* ... */

struct device {
	/* ... */
};

/* From include/linux/compiler-gcc.h */
#define __printf(a, b)			__attribute__((format(printf, a, b)))

/* From include/linux/kern_levels.h */
#define KERN_SOH	"\001"		/* ASCII Start Of Header */
#define KERN_DEBUG	KERN_SOH "7"	/* debug-level messages */

#ifdef CONFIG_PRINTK

/* ... */

extern __printf(3, 4)
int dev_printk(const char *level, const struct device *dev,
	       const char *fmt, ...);

extern __printf(2, 3)
int dev_err(const struct device *dev, const char *fmt, ...);

extern __printf(2, 3)
int dev_warn(const struct device *dev, const char *fmt, ...);

extern __printf(2, 3)
int _dev_info(const struct device *dev, const char *fmt, ...);

/* ... */

#else

/* ... */

static inline __printf(3, 4)
int dev_printk(const char *level, const struct device *dev,
	       const char *fmt, ...)
{ return 0; }

static inline __printf(2, 3)
int dev_err(const struct device *dev, const char *fmt, ...)
{ return 0; }

static inline __printf(2, 3)
int dev_warn(const struct device *dev, const char *fmt, ...)
{ return 0; }

static inline __printf(2, 3)
int _dev_info(const struct device *dev, const char *fmt, ...)
{ return 0; }

/* ... */

#endif

#define dev_info(dev, fmt, arg...) _dev_info(dev, fmt, ##arg)

#if defined(DEBUG)
#define dev_dbg(dev, format, arg...)		\
	dev_printk(KERN_DEBUG, dev, format, ##arg)
#else
#define dev_dbg(dev, format, arg...)				\
({								\
	if (0)							\
		dev_printk(KERN_DEBUG, dev, format, ##arg);	\
	0;							\
})
#endif

#endif /* _DEVICE_H_ */
