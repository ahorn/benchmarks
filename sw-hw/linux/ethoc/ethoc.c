/*
 * Simplified linux/drivers/net/ethernet/ethoc.c
 *
 * Copyright (C) 2007-2008 Avionic Design Development GmbH
 * Copyright (C) 2008-2009 Avionic Design GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Written by Thierry Reding <thierry.reding@avionic-design.de>
 */

#ifndef _CBMC_
#include <assert.h>
#endif

#include "sw-hw.h"
#include "kernel.h"
#include "errno.h"
#include "crc32.h"
#include "if.h"
#include "log2.h"
#include "device.h"
#include "etherdevice.h"
#include "netdevice.h"
#include "if_ether.h"

#include "ethoc/opencores_eth.h"
#include "ethoc/sys.h"
#include "ethoc/osdep.h"

#define DMA_BUF_SIZE	0x40000 /* 8 KiB */

/* register offsets */
#define	MODER		0x00
#define	INT_SOURCE	0x04
#define	INT_MASK	0x08
#define	IPGT		0x0c
#define	IPGR1		0x10
#define	IPGR2		0x14
#define	PACKETLEN	0x18
#define	COLLCONF	0x1c
#define	TX_BD_NUM	0x20
#define	CTRLMODER	0x24
#define	MIIMODER	0x28
#define	MIICOMMAND	0x2c
#define	MIIADDRESS	0x30
#define	MIITX_DATA	0x34
#define	MIIRX_DATA	0x38
#define	MIISTATUS	0x3c
#define	MAC_ADDR0	0x40
#define	MAC_ADDR1	0x44
#define	ETH_HASH0	0x48
#define	ETH_HASH1	0x4c
#define	ETH_TXCTRL	0x50

/* mode register */
#define	MODER_RXEN	(1 <<  0) /* receive enable */
#define	MODER_TXEN	(1 <<  1) /* transmit enable */
#define	MODER_NOPRE	(1 <<  2) /* no preamble */
#define	MODER_BRO	(1 <<  3) /* broadcast address */
#define	MODER_IAM	(1 <<  4) /* individual address mode */
#define	MODER_PRO	(1 <<  5) /* promiscuous mode */
#define	MODER_IFG	(1 <<  6) /* interframe gap for incoming frames */
#define	MODER_LOOP	(1 <<  7) /* loopback */
#define	MODER_NBO	(1 <<  8) /* no back-off */
#define	MODER_EDE	(1 <<  9) /* excess defer enable */
#define	MODER_FULLD	(1 << 10) /* full duplex */
#define	MODER_RESET	(1 << 11) /* FIXME: reset (undocumented) */
#define	MODER_DCRC	(1 << 12) /* delayed CRC enable */
#define	MODER_CRC	(1 << 13) /* CRC enable */
#define	MODER_HUGE	(1 << 14) /* huge packets enable */
#define	MODER_PAD	(1 << 15) /* padding enabled */
#define	MODER_RSM	(1 << 16) /* receive small packets */

/* interrupt source and mask registers */
#define	INT_MASK_TXF	(1 << 0) /* transmit frame */
#define	INT_MASK_TXE	(1 << 1) /* transmit error */
#define	INT_MASK_RXF	(1 << 2) /* receive frame */
#define	INT_MASK_RXE	(1 << 3) /* receive error */
#define	INT_MASK_BUSY	(1 << 4)
#define	INT_MASK_TXC	(1 << 5) /* transmit control frame */
#define	INT_MASK_RXC	(1 << 6) /* receive control frame */

#define	INT_MASK_TX	(INT_MASK_TXF | INT_MASK_TXE)
#define	INT_MASK_RX	(INT_MASK_RXF | INT_MASK_RXE)

#define	INT_MASK_ALL ( \
		INT_MASK_TXF | INT_MASK_TXE | \
		INT_MASK_RXF | INT_MASK_RXE | \
		INT_MASK_TXC | INT_MASK_RXC | \
		INT_MASK_BUSY \
	)

/* packet length register */
#define	PACKETLEN_MIN(min)		(((min) & 0xffff) << 16)
#define	PACKETLEN_MAX(max)		(((max) & 0xffff) <<  0)
#define	PACKETLEN_MIN_MAX(min, max)	(PACKETLEN_MIN(min) | \
					PACKETLEN_MAX(max))

/* transmit buffer number register */
#define	TX_BD_NUM_VAL(x)	(((x) <= 0x80) ? (x) : 0x80)

/* control module mode register */
#define	CTRLMODER_PASSALL	(1 << 0) /* pass all receive frames */
#define	CTRLMODER_RXFLOW	(1 << 1) /* receive control flow */
#define	CTRLMODER_TXFLOW	(1 << 2) /* transmit control flow */

/* MII mode register */
#define	MIIMODER_CLKDIV(x)	((x) & 0xfe) /* needs to be an even number */
#define	MIIMODER_NOPRE		(1 << 8) /* no preamble */

/* MII command register */
#define	MIICOMMAND_SCAN		(1 << 0) /* scan status */
#define	MIICOMMAND_READ		(1 << 1) /* read status */
#define	MIICOMMAND_WRITE	(1 << 2) /* write control data */

/* MII address register */
#define	MIIADDRESS_FIAD(x)		(((x) & 0x1f) << 0)
#define	MIIADDRESS_RGAD(x)		(((x) & 0x1f) << 8)
#define	MIIADDRESS_ADDR(phy, reg)	(MIIADDRESS_FIAD(phy) | \
					MIIADDRESS_RGAD(reg))

/* MII transmit data register */
#define	MIITX_DATA_VAL(x)	((x) & 0xffff)

/* MII receive data register */
#define	MIIRX_DATA_VAL(x)	((x) & 0xffff)

/* MII status register */
#define	MIISTATUS_LINKFAIL	(1 << 0)
#define	MIISTATUS_BUSY		(1 << 1)
#define	MIISTATUS_INVALID	(1 << 2)

/* TX buffer descriptor */
#define	TX_BD_CS		(1 <<  0) /* carrier sense lost */
#define	TX_BD_DF		(1 <<  1) /* defer indication */
#define	TX_BD_LC		(1 <<  2) /* late collision */
#define	TX_BD_RL		(1 <<  3) /* retransmission limit */
#define	TX_BD_RETRY_MASK	(0x00f0)
#define	TX_BD_RETRY(x)		(((x) & 0x00f0) >>  4)
#define	TX_BD_UR		(1 <<  8) /* transmitter underrun */
#define	TX_BD_CRC		(1 << 11) /* TX CRC enable */
#define	TX_BD_PAD		(1 << 12) /* pad enable for short packets */
#define	TX_BD_WRAP		(1 << 13)
#define	TX_BD_IRQ		(1 << 14) /* interrupt request enable */
#define	TX_BD_READY		(1 << 15) /* TX buffer ready */
#define	TX_BD_LEN(x)		(((x) & 0xffff) << 16)
#define	TX_BD_LEN_MASK		(0xffff << 16)

#define	TX_BD_STATS		(TX_BD_CS | TX_BD_DF | TX_BD_LC | \
				TX_BD_RL | TX_BD_RETRY_MASK | TX_BD_UR)

/* RX buffer descriptor */
#define	RX_BD_LC	(1 <<  0) /* late collision */
#define	RX_BD_CRC	(1 <<  1) /* RX CRC error */
#define	RX_BD_SF	(1 <<  2) /* short frame */
#define	RX_BD_TL	(1 <<  3) /* too long */
#define	RX_BD_DN	(1 <<  4) /* dribble nibble */
#define	RX_BD_IS	(1 <<  5) /* invalid symbol */
#define	RX_BD_OR	(1 <<  6) /* receiver overrun */
#define	RX_BD_MISS	(1 <<  7)
#define	RX_BD_CF	(1 <<  8) /* control frame */
#define	RX_BD_WRAP	(1 << 13)
#define	RX_BD_IRQ	(1 << 14) /* interrupt request enable */
#define	RX_BD_EMPTY	(1 << 15)
#define	RX_BD_LEN(x)	(((x) & 0xffff) << 16)

#define	RX_BD_STATS	(RX_BD_LC | RX_BD_CRC | RX_BD_SF | RX_BD_TL | \
			RX_BD_DN | RX_BD_IS | RX_BD_OR | RX_BD_MISS)

#define	ETHOC_BUFSIZ		1536
#define	ETHOC_ZLEN		64
#define	ETHOC_BD_BASE		0x400
#define	ETHOC_TIMEOUT		(HZ / 2)
#define	ETHOC_MII_TIMEOUT	(1 + (HZ / 5))

/**
 * struct ethoc - driver-private device structure
 * @num_tx:		number of send buffers
 * @cur_tx:		last send buffer written
 * @dty_tx:		last buffer actually sent
 * @num_rx:		number of receive buffers
 * @cur_rx:		current receive buffer
 * @dma_regions:	array of pointers to DMA area
 * @netdev:		pointer to network device structure
 * @napi:		NAPI structure
 * @phy_id:		address of attached PHY
 */
struct ethoc {
	unsigned int num_tx;
	unsigned int cur_tx;
	unsigned int dty_tx;

	unsigned int num_rx;
	unsigned int cur_rx;

	/* Assume the thread which acknowledges the TX or RX is also
 	 * the one which reads this DMA buffer. In the case of RX, this
 	 * establishes the required happens-before order between the
 	 * hardware writing the DMA buffer and the software reading it.
 	 */
	void *dma_buf;
	void **dma_regions;

	struct net_device *netdev;
	struct napi_struct napi;

	s8 phy_id;

        OpenEthState *open_eth;
};

/**
 * struct ethoc_bd - buffer descriptor
 * @stat:	buffer statistics
 * @addr:	physical memory address
 *
 * Concurrency synchronization between the software and hardware
 * is done through the RX_BD_EMPTY and TX_BD_READY bits.
 *
 * The low-level software sets the RX_BD_EMPTY bit to a `0'
 * once the hardware is allowed to write the DMA buffer on
 * an incoming packet. Usually, this is only done after the
 * DMA buffer content has been passed on to a socket layer.
 * The MAC, in turn, sets the RX_BD_EMPTY bit to a `1' before
 * it overwrites the DMA buffer associated with a buffer
 * descriptor.
 *
 * Similarly, the low-level software sets the TX_BD_READY
 * bit to a `1' if it has written the DMA buffer which
 * contains the content to be transmitted.
 *
 * @see_also: Section 4.2.2.x in data sheet
 */
struct ethoc_bd {
	u32 stat;
	u32 addr;
};

/* Calls OpenCores Ethernet MAC model */
static inline u32 ethoc_read(struct ethoc *dev, loff_t offset)
{
        return open_eth_reg_read(dev->open_eth, offset);
}

/* Calls OpenCores Ethernet MAC model */
static inline void ethoc_write(struct ethoc *dev, loff_t offset, u32 data)
{
        open_eth_reg_write(dev->open_eth, offset, data);
}

/* Calls OpenCores Ethernet MAC model */
static inline void ethoc_read_bd(struct ethoc *dev, int index,
		struct ethoc_bd *bd)
{
	const hwaddr addr = index * sizeof(struct ethoc_bd);
	const uint64_t desc_dword = open_eth_desc_read(dev->open_eth, addr);

	bd->stat = desc_dword & 0xffffffffLL;
	bd->addr = (desc_dword >> 32) & 0xffffffffLL;
}

/* Calls OpenCores Ethernet MAC model */
static inline void ethoc_write_bd(struct ethoc *dev, int index,
		const struct ethoc_bd *bd)
{
	const hwaddr addr = index * sizeof(struct ethoc_bd);
        uint64_t desc;

        desc = bd->addr;
	desc <<= 32;
        desc |= bd->stat;

	open_eth_desc_write(dev->open_eth, addr, desc);
}

static inline void ethoc_enable_irq(struct ethoc *dev, u32 mask)
{
	u32 imask = ethoc_read(dev, INT_MASK);
	imask |= mask;
	ethoc_write(dev, INT_MASK, imask);
}

static inline void ethoc_disable_irq(struct ethoc *dev, u32 mask)
{
	u32 imask = ethoc_read(dev, INT_MASK);
	imask &= ~mask;
	ethoc_write(dev, INT_MASK, imask);
}

static inline void ethoc_ack_irq(struct ethoc *dev, u32 mask)
{
	ethoc_write(dev, INT_SOURCE, mask);
}

static inline void ethoc_enable_rx_and_tx(struct ethoc *dev)
{
	u32 mode = ethoc_read(dev, MODER);
	mode |= MODER_RXEN | MODER_TXEN;
	ethoc_write(dev, MODER, mode);
}

static inline void ethoc_disable_rx_and_tx(struct ethoc *dev)
{
	u32 mode = ethoc_read(dev, MODER);
	mode &= ~(MODER_RXEN | MODER_TXEN);
	ethoc_write(dev, MODER, mode);
}

static int ethoc_init_ring(struct ethoc *dev, unsigned long mem_start)
{
	struct ethoc_bd bd;
	int i;
	void *buf;

	dev->cur_tx = 0;
	dev->dty_tx = 0;
	dev->cur_rx = 0;
	buf = dev->dma_buf;

	ethoc_write(dev, TX_BD_NUM, dev->num_tx);

	/* setup transmission buffers */
	bd.addr = mem_start & 0xffffffffL;
	bd.stat = TX_BD_IRQ | TX_BD_CRC;

	for (i = 0; i < dev->num_tx; i++) {
		if (i == dev->num_tx - 1)
			bd.stat |= TX_BD_WRAP;

		ethoc_write_bd(dev, i, &bd);
		bd.addr += ETHOC_BUFSIZ;

		dev->dma_regions[i] = buf;
		buf += ETHOC_BUFSIZ;
	}

	bd.stat = RX_BD_EMPTY | RX_BD_IRQ;

	struct ethoc_bd new_bd;
	for (i = 0; i < dev->num_rx; i++) {
		if (i == dev->num_rx - 1)
			bd.stat |= RX_BD_WRAP;

		ethoc_write_bd(dev, dev->num_tx + i, &bd);
		dev->dma_regions[dev->num_tx + i] = buf;

		bd.addr += ETHOC_BUFSIZ;
		buf += ETHOC_BUFSIZ;
	}

	return 0;
}

static int ethoc_reset(struct ethoc *dev)
{
	u32 mode;

	/* TODO: reset controller? */

	ethoc_disable_rx_and_tx(dev);

	/* TODO: setup registers */

	/* enable FCS generation and automatic padding */
	mode = ethoc_read(dev, MODER);
	mode |= MODER_CRC | MODER_PAD;
	ethoc_write(dev, MODER, mode);

	/* set full-duplex mode */
	mode = ethoc_read(dev, MODER);
	mode |= MODER_FULLD;
	ethoc_write(dev, MODER, mode);
	ethoc_write(dev, IPGT, 0x15);

	ethoc_ack_irq(dev, INT_MASK_ALL);
	ethoc_enable_irq(dev, INT_MASK_ALL);
	ethoc_enable_rx_and_tx(dev);
	return 0;
}

static unsigned int ethoc_update_rx_stats(struct ethoc *dev,
		struct ethoc_bd *bd)
{
	struct net_device *netdev = dev->netdev;
	unsigned int ret = 0;

	if (bd->stat & RX_BD_TL) {
		dev_err(&netdev->dev, "RX: frame too long\n");
		netdev->stats.rx_length_errors++;
		ret++;
	}

	if (bd->stat & RX_BD_SF) {
		dev_err(&netdev->dev, "RX: frame too short\n");
		netdev->stats.rx_length_errors++;
		ret++;
	}

	if (bd->stat & RX_BD_DN) {
		dev_err(&netdev->dev, "RX: dribble nibble\n");
		netdev->stats.rx_frame_errors++;
	}

	if (bd->stat & RX_BD_CRC) {
		dev_err(&netdev->dev, "RX: wrong CRC\n");
		netdev->stats.rx_crc_errors++;
		ret++;
	}

	if (bd->stat & RX_BD_OR) {
		dev_err(&netdev->dev, "RX: overrun\n");
		netdev->stats.rx_over_errors++;
		ret++;
	}

	if (bd->stat & RX_BD_MISS)
		netdev->stats.rx_missed_errors++;

	if (bd->stat & RX_BD_LC) {
		dev_err(&netdev->dev, "RX: late collision\n");
		netdev->stats.collisions++;
		ret++;
	}

	return ret;
}

/**
 * ethoc_rx - receives packets up to a certain number
 * @dev:	generic network device
 * @limit:	upper bound on the number of packets to receive
 *
 * Returns the number of packets processed. The return value is always
 * less than or equal to @limit.
 */
static int ethoc_rx(struct net_device *dev, int limit)
{
	struct ethoc *priv = netdev_priv(dev);
	int count;
	u32 mask;

	for (count = 0; count < limit; ++count) {
		unsigned int entry;
		struct ethoc_bd bd;

		entry = priv->num_tx + priv->cur_rx;
		ethoc_read_bd(priv, entry, &bd);
		if (bd.stat & RX_BD_EMPTY) {
			ethoc_ack_irq(priv, INT_MASK_RX);
			/* If packet (interrupt) came in between checking
			 * BD_EMTPY and clearing the interrupt source, then we
			 * risk missing the packet as the RX interrupt won't
			 * trigger right away when we reenable it; hence, check
			 * BD_EMTPY here again to make sure there isn't such a
			 * packet waiting for us...
			 */
			ethoc_read_bd(priv, entry, &bd);
			if (bd.stat & RX_BD_EMPTY)
				break;
		}

		if (ethoc_update_rx_stats(priv, &bd) == 0) {
			/* For the experiments, we removed the skb (socket) calls and
 			 * the possibility of insufficient memory or dropped packets.
 			 */
			int size = bd.stat >> 16;
			size -= 4; /* strip the CRC */

			void *src = priv->dma_regions[entry];

			dev->stats.rx_packets++;
			dev->stats.rx_bytes += size;
		}

		/* clear the buffer descriptor so it can be reused */
		bd.stat &= ~RX_BD_STATS;
		bd.stat |=  RX_BD_EMPTY;
		ethoc_write_bd(priv, entry, &bd);
		if (++priv->cur_rx == priv->num_rx)
			priv->cur_rx = 0;
	}

	return count;
}

static void ethoc_update_tx_stats(struct ethoc *dev, struct ethoc_bd *bd)
{
	struct net_device *netdev = dev->netdev;

	if (bd->stat & TX_BD_LC) {
		dev_err(&netdev->dev, "TX: late collision\n");
		netdev->stats.tx_window_errors++;
	}

	if (bd->stat & TX_BD_RL) {
		dev_err(&netdev->dev, "TX: retransmit limit\n");
		netdev->stats.tx_aborted_errors++;
	}

	if (bd->stat & TX_BD_UR) {
		dev_err(&netdev->dev, "TX: underrun\n");
		netdev->stats.tx_fifo_errors++;
	}

	if (bd->stat & TX_BD_CS) {
		dev_err(&netdev->dev, "TX: carrier sense lost\n");
		netdev->stats.tx_carrier_errors++;
	}

	if (bd->stat & TX_BD_STATS)
		netdev->stats.tx_errors++;

	netdev->stats.collisions += (bd->stat >> 4) & 0xf;
	netdev->stats.tx_bytes += bd->stat >> 16;
	netdev->stats.tx_packets++;
}

static int ethoc_tx(struct net_device *dev, int limit)
{
	struct ethoc *priv = netdev_priv(dev);
	int count;
	struct ethoc_bd bd;

	for (count = 0; count < limit; ++count) {
		unsigned int entry;

		entry = priv->dty_tx & (priv->num_tx-1);

		ethoc_read_bd(priv, entry, &bd);

		if (bd.stat & TX_BD_READY || (priv->dty_tx == priv->cur_tx)) {
			ethoc_ack_irq(priv, INT_MASK_TX);
			/* If interrupt came in between reading in the BD
			 * and clearing the interrupt source, then we risk
			 * missing the event as the TX interrupt won't trigger
			 * right away when we reenable it; hence, check
			 * BD_EMPTY here again to make sure there isn't such an
			 * event pending...
			 */
			ethoc_read_bd(priv, entry, &bd);
			if (bd.stat & TX_BD_READY ||
			    (priv->dty_tx == priv->cur_tx))
				break;
		}

		ethoc_update_tx_stats(priv, &bd);
		priv->dty_tx++;
	}

	if ((priv->cur_tx - priv->dty_tx) <= (priv->num_tx / 2))
		netif_wake_queue(dev);

	return count;
}

static irqreturn_t ethoc_interrupt(void *opaque, int n, int level)
{
	OpenEthState *open_eth = (OpenEthState *) opaque;
	struct net_device *dev = (struct net_device *) open_eth->software;

	struct ethoc *priv = netdev_priv(dev);
	u32 pending;
	u32 mask;

	/* Figure out what triggered the interrupt...
	 * The tricky bit here is that the interrupt source bits get
	 * set in INT_SOURCE for an event regardless of whether that
	 * event is masked or not.  Thus, in order to figure out what
	 * triggered the interrupt, we need to remove the sources
	 * for all events that are currently masked.  This behaviour
	 * is not particularly well documented but reasonable...
	 */
	mask = ethoc_read(priv, INT_MASK);
	pending = ethoc_read(priv, INT_SOURCE);
	pending &= mask;

	if (unlikely(pending == 0)) {
		return IRQ_NONE;
	}

	ethoc_ack_irq(priv, pending);

	/* We always handle the dropped packet interrupt */
	if (pending & INT_MASK_BUSY) {
		dev_err(&dev->dev, "packet dropped\n");
		dev->stats.rx_dropped++;
	}

	/* Handle receive/transmit event by switching to polling */
	if (pending & (INT_MASK_TX | INT_MASK_RX)) {
		ethoc_disable_irq(priv, INT_MASK_TX | INT_MASK_RX);
		napi_schedule(&priv->napi);
	}

	return IRQ_HANDLED;
}

static int ethoc_get_mac_address(struct net_device *dev, void *addr)
{
	struct ethoc *priv = netdev_priv(dev);
	u8 *mac = (u8 *)addr;
	u32 reg;

	reg = ethoc_read(priv, MAC_ADDR0);
	mac[2] = (reg >> 24) & 0xff;
	mac[3] = (reg >> 16) & 0xff;
	mac[4] = (reg >>  8) & 0xff;
	mac[5] = (reg >>  0) & 0xff;

	reg = ethoc_read(priv, MAC_ADDR1);
	mac[0] = (reg >>  8) & 0xff;
	mac[1] = (reg >>  0) & 0xff;

	return 0;
}

/**
 * Only one ethoc_poll is guaranteed to execute at the same time.
 */
static int ethoc_poll(struct napi_struct *napi, int budget)
{
	struct ethoc *priv = container_of(napi, struct ethoc, napi);
	int rx_work_done = 0;
	int tx_work_done = 0;

	rx_work_done = ethoc_rx(priv->netdev, budget);
	tx_work_done = ethoc_tx(priv->netdev, budget);

	if (rx_work_done < budget && tx_work_done < budget) {
		napi_complete(napi);
		ethoc_enable_irq(priv, INT_MASK_TX | INT_MASK_RX);
	}

	return rx_work_done;
}

static int ethoc_mdio_read(struct ethoc *priv, int phy, int reg)
{
	int i;

	ethoc_write(priv, MIIADDRESS, MIIADDRESS_ADDR(phy, reg));
	ethoc_write(priv, MIICOMMAND, MIICOMMAND_READ);

	for (i=0; i < 5; i++) {
		u32 status = ethoc_read(priv, MIISTATUS);
		if (!(status & MIISTATUS_BUSY)) {
			u32 data = ethoc_read(priv, MIIRX_DATA);
			/* reset MII command register */
			ethoc_write(priv, MIICOMMAND, 0);
			return data;
		}
		usleep_range(100,200);
	}

	return -EBUSY;
}

static int ethoc_mdio_write(struct ethoc *priv, int phy, int reg, u16 val)
{
	int i;

	ethoc_write(priv, MIIADDRESS, MIIADDRESS_ADDR(phy, reg));
	ethoc_write(priv, MIITX_DATA, val);
	ethoc_write(priv, MIICOMMAND, MIICOMMAND_WRITE);

	for (i=0; i < 5; i++) {
		u32 stat = ethoc_read(priv, MIISTATUS);
		if (!(stat & MIISTATUS_BUSY)) {
			/* reset MII command register */
			ethoc_write(priv, MIICOMMAND, 0);
			return 0;
		}
		usleep_range(100,200);
	}

	return -EBUSY;
}

/* ... */

static int ethoc_open(struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);

	/* ... */

	ethoc_init_ring(priv, dev->mem_start);
	ethoc_reset(priv);

	if (netif_queue_stopped(dev)) {
		dev_dbg(&dev->dev, " resuming queue\n");
		netif_wake_queue(dev);
	} else {
		dev_dbg(&dev->dev, " starting queue\n");
		netif_start_queue(dev);
	}

	napi_enable(&priv->napi);

	/* ... */

	return 0;
}

static int ethoc_stop(struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);

	napi_disable(&priv->napi);

	ethoc_disable_rx_and_tx(priv);

	/* ... */

	return 0;
}

static int ethoc_set_mac_address(struct net_device *dev, const void *addr)
{
	struct ethoc *priv = netdev_priv(dev);
	u8 *mac = (u8 *)addr;

	if (!is_valid_ether_addr(mac))
		return -EADDRNOTAVAIL;

	ethoc_write(priv, MAC_ADDR0, (mac[2] << 24) | (mac[3] << 16) |
				     (mac[4] <<  8) | (mac[5] <<  0));
	ethoc_write(priv, MAC_ADDR1, (mac[0] <<  8) | (mac[1] <<  0));

	return 0;
}

static void ethoc_set_multicast_list(struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);
	u32 mode = ethoc_read(priv, MODER);
	struct netdev_hw_addr *ha;
	u32 hash[2] = { 0, 0 };

	/* set loopback mode if requested */
	if (dev->flags & IFF_LOOPBACK)
		mode |=  MODER_LOOP;
	else
		mode &= ~MODER_LOOP;

	/* receive broadcast frames if requested */
	if (dev->flags & IFF_BROADCAST)
		mode &= ~MODER_BRO;
	else
		mode |=  MODER_BRO;

	/* enable promiscuous mode if requested */
	if (dev->flags & IFF_PROMISC)
		mode |=  MODER_PRO;
	else
		mode &= ~MODER_PRO;

	ethoc_write(priv, MODER, mode);

	/* receive multicast frames */
	if (dev->flags & IFF_ALLMULTI) {
		hash[0] = 0xffffffff;
		hash[1] = 0xffffffff;
	} else {
		netdev_for_each_mc_addr(ha, dev) {
			u32 crc = ether_crc(ETH_ALEN, ha->addr);
			int bit = (crc >> 26) & 0x3f;
			hash[bit >> 5] |= 1 << (bit & 0x1f);
		}
	}

	ethoc_write(priv, ETH_HASH0, hash[0]);
	ethoc_write(priv, ETH_HASH1, hash[1]);
}

/* ... */

/**
 * Model system memory which can hold at least 128 Ethernet packets.
 * Since we do not analyze the virtual memory manager (e.g. page tables),
 * all addresses can only directly refer to positions in this array.
 *
 * Any memory after the 128 * ETHOC_BUFSIZ boundary is invalid.
 */
static u8 dma_buf[DMA_BUF_SIZE];
static void *dma_regions[DMA_BUF_SIZE / ETHOC_BUFSIZ];
static unsigned int packet_sizes[DMA_BUF_SIZE / ETHOC_BUFSIZ];
static u8 packet_bytes[DMA_BUF_SIZE / ETHOC_BUFSIZ];

#define PACKET_VC_INDEX 6

#define OPEN_ETH_STATE(nc) \
    ((OpenEthState *) container_of(nc, NICState, nc)->opaque)

static NetClientState *nc;

/**
 * This function is a lightweight thread which triggers an RX event in the
 * OpenCores Ethernet MAC hardware model.
 *
 * Each packet is associated with a unique positive identifier (packet_id).
 * In addition, we require that the global arrays satisfy the equalities
 * 
 * 	packet_bytes[packet_id - 1] == data and packet_sizes[packet_id - 1] == packet_size
 *
 * prior to executing this function as a thread.
 *
 * For thread-safety, this function does not modify these arrays.
 */
static void test_rx(const u8* mac_addr, int packet_id, u8 data, unsigned int packet_size)
{
	uint8_t packet[ETHOC_BUFSIZ];

	/* set destination address in the packet, i.e. the address of the
 	 * OpenCores Ethernet MAC hardware model.
 	 */
	int i;
	for (i = 0; i < 6; i++) {
		packet[i] = mac_addr[i];
	}

	/* Ensure the seventh byte of the packet stores an identifier
 	 * which allow us to validate the content of the packet after
 	 * the driver has received the packet (our analysis does not
 	 * consider undelivered packets).
 	 *
 	 * See also the preconditions of this function.
	 */
	packet[PACKET_VC_INDEX] = packet_id;

	/* pad the rest of the packet with the supplied data */
	memset(packet + PACKET_VC_INDEX + 1, data, packet_size - (PACKET_VC_INDEX + 1));

	/* Since this thread could be waiting while ethoc_stop() is called, we must
 	 * check if the hardware model can still receive packets. The assumption is
 	 * that reading the registers of the hardware model is not a volatile
 	 * operation (i.e. values are not cached).
 	 */ 
	if (open_eth_can_receive(OPEN_ETH_STATE(nc))) {

		/* Trigger incoming packet in hardware model.
		 *
 		 * This call must NOT be asynchronous because the packet array
 		 * could otherwise be deallocated from the stack causing a
 		 * memory error.
 		 */
		open_eth_receive(OPEN_ETH_STATE(nc), packet, packet_size);
	}
}

int main(void)
{
        /* In our analysis, we force these variables to be non-deterministic. */
	const int irq_n = nondet_int(3);
	const unsigned int flags = nondet_uint(0);

	/* Empty implementation of virtual machine Net API */
	NetClientInfo nc_info;
	nc_info.can_receive = NULL;
	nc_info.receive = NULL;
	nc_info.link_status_changed = NULL;

	/* Virtual machine NIC which is setup to receive
 	 * (but not transmit) packets. */
	NICState nic;
	nic.nc.info = &nc_info;
	nic.nc.link_down = 0;
	nic.nc.peer = NULL;
	nic.nc.receive_disabled = 0;

	/* Virtual hardware interrupt for incoming packets */
	IRQState irq;
	irq.n = irq_n;
	irq.handler = ethoc_interrupt;

	/* Ethernet MAC hardware model */
	OpenEthState open_eth;
	open_eth.nic = &nic;
	open_eth.irq = &irq;
	open_eth.mii.link_ok = true;

	irq.opaque = &open_eth;

	memset(open_eth.mii.regs, 0, sizeof(open_eth.mii.regs));
	memset(open_eth.regs, 0, sizeof(open_eth.regs));
	memset(open_eth.desc, 0, sizeof(open_eth.desc));

	nic.opaque = &open_eth;
	nc = &nic.nc;

	/* reset MAC and MII */
	open_eth_reg_write(&open_eth, open_eth_reg(MODER), MODER_RST);

	struct net_device netdev;
	struct ethoc ethoc;

	netdev.priv = &ethoc;
	netdev.flags = flags;

	netdev.stats.rx_packets = 0;
	netdev.stats.tx_packets = 0;
	netdev.stats.rx_bytes = 0;
	netdev.stats.tx_bytes = 0;
	netdev.stats.rx_errors = 0;
	netdev.stats.tx_errors = 0;
	netdev.stats.rx_dropped = 0;
	netdev.stats.tx_dropped = 0;
	netdev.stats.multicast = 0;
	netdev.stats.collisions = 0;
	netdev.stats.rx_length_errors = 0;
	netdev.stats.rx_over_errors = 0;
	netdev.stats.rx_crc_errors = 0;
	netdev.stats.rx_frame_errors = 0;
	netdev.stats.rx_fifo_errors = 0;
	netdev.stats.rx_missed_errors = 0;
	netdev.stats.tx_aborted_errors = 0;
	netdev.stats.tx_carrier_errors = 0;
	netdev.stats.tx_fifo_errors = 0;
	netdev.stats.tx_heartbeat_errors = 0;
	netdev.stats.tx_window_errors = 0;
	netdev.stats.rx_compressed = 0;
	netdev.stats.tx_compressed = 0;

	ethoc.phy_id = DEFAULT_PHY;
	ethoc.open_eth = &open_eth;
	ethoc.netdev = &netdev;

	ethoc.napi.poll = ethoc_poll;
	ethoc.napi.sched = 1;
	ethoc.napi.complete = 0;
	ethoc.napi.is_disabling = 0;

	/* use a non-deterministic NAPI weight in the range [0, 512] */
	ethoc.napi.weight = nondet_int(64);
	if (ethoc.napi.weight < 0 || ethoc.napi.weight > 512)
		return 1;

	open_eth.software = &netdev;

        /* In our analysis, we force these variables to be non-deterministic.
 	 * The values are constraint by the next two conditional statements.
 	 */
	const u8 mac_addr[6] = { nondet_u8(0x10),
				 nondet_u8(0x32),
				 nondet_u8(0x54),
				 nondet_u8(0x76),
				 nondet_u8(0x98),
				 nondet_u8(0xba) };

	const long mem_size = nondet_long(ETHOC_BUFSIZ * 12);

	if (!is_valid_ether_addr(mac_addr))
		return 1;
	if (DMA_BUF_SIZE < mem_size || mem_size <= (4 * ETHOC_BUFSIZ))
		return 1;

	/* setup virtual machine memory address space */
	cpu_physical_memory_init((uintptr_t) dma_buf);

	netdev.mem_start = (unsigned long) dma_buf;
	netdev.mem_end = netdev.mem_start + mem_size;
	ethoc.dma_buf = dma_buf;
	ethoc.dma_regions = dma_regions;

	/* calculate the number of TX/RX buffers, maximum 128 supported */
	int num_bd = min_t(unsigned int,
		128, (netdev.mem_end - netdev.mem_start + 1) / ETHOC_BUFSIZ);
	if (num_bd < 4) {
		return 1;
	}
	/* num_tx must be a power of two */
	ethoc.num_tx = rounddown_pow_of_two(num_bd >> 1);
	ethoc.num_rx = num_bd - ethoc.num_tx;

	const unsigned int rx_packet_num = nondet_int(3);
	if (rx_packet_num > ethoc.num_rx)
		return;

	ethoc_set_mac_address(&netdev, mac_addr);
	ethoc_open(&netdev);

	int packet_id;
	for (packet_id = 0; packet_id < rx_packet_num; packet_id++) {
		const unsigned int packet_size = nondet_uint(64 + packet_id);
		if (packet_size >= ETHOC_BUFSIZ || packet_size < 64)
			continue;

		packet_sizes[packet_id] = packet_size;
		packet_bytes[packet_id] = nondet_u8((packet_id + 1) % 255);

		/* Start an asynchronous call which triggers an incoming packet.
 		 * Each packet is associated with a unique positive identifier.
 		 */
		test_rx(mac_addr, packet_id + 1, packet_bytes[packet_id], packet_sizes[packet_id]);
	}
}
