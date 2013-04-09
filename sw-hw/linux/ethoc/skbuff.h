/*
 *	Definitions for the 'struct sk_buff' memory handlers.
 *
 *	Authors:
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *		Florian La Roche, <rzsfl@rz.uni-sb.de>
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 */

#ifndef _LINUX_SKBUFF_H
#define _LINUX_SKBUFF_H

/* ... */

/** 
 *	struct sk_buff - sliced socket buffer
 *	@len: Length of actual data
 *	@data: Data head pointer
 */

struct sk_buff {
	/* ... */

	unsigned int		len;

	/* ... */

	unsigned char		*data;

	/* ... */
};

/* ... */

/**
 * skb_tx_timestamp() - Driver hook for transmit timestamping
 *
 * Ethernet MAC Drivers should call this function in their hard_xmit()
 * function immediately before giving the sk_buff to the MAC hardware.
 *
 * @skb: A socket buffer.
 */
static inline void skb_tx_timestamp(struct sk_buff *skb)
{
	/* ... */
}

#endif	/* _LINUX_SKBUFF_H */
