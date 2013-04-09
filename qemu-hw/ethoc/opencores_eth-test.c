/*
 * Unit tests for OpenCores Ethernet MAC 10/100
 *
 * Copyright (C) 2012 Alex Horn <alex.horn@cs.ox.ac.uk>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later. See the COPYING file in the top-level directory.
 */
#include <assert.h>
#include <stddef.h>

#include "opencores_eth.h"
#include "net.h"
#include "cpu.h"
#include "osdep.h"
#include "sys.h"

#define OPEN_ETH_STATE(nc) \
    ((OpenEthState *) container_of(nc, NICState, nc)->opaque)

static NetClientState *nc;

static void test_init(void)
{
    OpenEthState *s = OPEN_ETH_STATE(nc);

    assert(0 == open_eth_reg_read(s, open_eth_reg(MODER)));
    assert(0 == open_eth_reg_read(s, open_eth_reg(IPGT)));
    assert(0 == open_eth_reg_read(s, open_eth_reg(IPGR1)));
    assert(0 == open_eth_reg_read(s, open_eth_reg(IPGR2)));
    assert(0 == open_eth_reg_read(s, open_eth_reg(PACKETLEN)));
    assert(0 == open_eth_reg_read(s, open_eth_reg(COLLCONF)));
    assert(0 == open_eth_reg_read(s, open_eth_reg(TX_BD_NUM)));
    assert(0 == open_eth_reg_read(s, open_eth_reg(MIIMODER)));

    /* reset MAC and MII */
    open_eth_reg_write(s, open_eth_reg(MODER), MODER_RST);

    assert(MODER_RST == open_eth_reg_read(s, open_eth_reg(MODER)));
    assert(0x12 == open_eth_reg_read(s, open_eth_reg(IPGT)));
    assert(0xc == open_eth_reg_read(s, open_eth_reg(IPGR1)));
    assert(0x12 == open_eth_reg_read(s, open_eth_reg(IPGR2)));
    assert(0x400600 == open_eth_reg_read(s, open_eth_reg(PACKETLEN)));
    assert(0xf003f == open_eth_reg_read(s, open_eth_reg(COLLCONF)));
    assert(0x40 == open_eth_reg_read(s, open_eth_reg(TX_BD_NUM)));
    assert(0x64 == open_eth_reg_read(s, open_eth_reg(MIIMODER)));
}

static unsigned raised_irq_count = 0;

static void test_rx(void)
{
    const uint64_t tx_bd_num = 0x40;
    uint64_t desc;
    hwaddr desc_addr;

    const uint8_t tx_packet[] = { /* recipient addr */
                                 0x12U, 0x34U, 0x56U,
                                 0x78U, 0x9AU, 0xBCU,
                                 /* data */
                                 0x20U, 0x21U, 0x22U,
                                 0x30U, 0x31U, 0x32U,
                                 0x40U, 0x41U, 0x42U,
                                 0x50U, 0x51U, 0x52U };

    /* setup rx DMA buffer */
    uint8_t rx_packet[sizeof(tx_packet)];
    memset(rx_packet, 0, sizeof(rx_packet));

    OpenEthState *s = OPEN_ETH_STATE(nc);

    /* reset MAC and MII */
    open_eth_reg_write(s, open_eth_reg(MODER), MODER_RST);
    assert(tx_bd_num == open_eth_reg_read(s, open_eth_reg(TX_BD_NUM)));

    /* setup MAC address */
    open_eth_reg_write(s, open_eth_reg(MAC_ADDR0), 0x56789ABC);
    open_eth_reg_write(s, open_eth_reg(MAC_ADDR1), 0x1234);

    /* enable IRQ for incoming packets */
    open_eth_reg_write(s, open_eth_reg(INT_MASK), INT_MASK_RXF_M);

    /* setup address map to allow 32 bit hardware addresses */
    cpu_physical_memory_init((uintptr_t) rx_packet);

    /* calculate lowest rx buffer descriptor address */
    desc_addr = tx_bd_num * 8;

    /* setup rx buffer descriptor for DMA on rx_packet */
    desc = (uint32_t) (uintptr_t) rx_packet;
    desc <<= 32;
    desc |= RXD_E | RXD_IRQ;
    open_eth_desc_write(s, desc_addr, desc);

    /* enable receiver */
    open_eth_reg_write(s, open_eth_reg(MODER), MODER_RXEN);

    /* trigger DMA operation and IRQ */
    raised_irq_count = 0;
    open_eth_receive(s, tx_packet, sizeof(tx_packet));

    /* validate DMA buffer content and IRQ */
    assert(sizeof(tx_packet) == sizeof(rx_packet));
    assert(memcmp(tx_packet, rx_packet, sizeof(tx_packet)) == 0);
    assert(raised_irq_count == 1);
}

// Must be annotated such that it can be read and written atomically
static unsigned peer_rx_count = 0;

static void atomic_increment_peer_rx_count()
{
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_begin();
#endif
#endif

    peer_rx_count++;

#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_end();
#endif
#endif
}

static void atomic_reset_peer_rx_count()
{
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_begin();
#endif
#endif

    peer_rx_count = 0;

#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_end();
#endif
#endif
}

static unsigned atomic_peer_rx_count()
{
    unsigned t;

#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_begin();
#endif
#endif

    t = peer_rx_count;

#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_end();
#endif
#endif

    return t;
}

static ssize_t peer_nc_open_eth_receive(NetClientState *nc,
                                     const uint8_t *buf, size_t size)
{
    atomic_increment_peer_rx_count();
    return 0;
}

static void peer_nc_open_eth_set_link_status(NetClientState *nc)
{
    return;
}

#define	TX_BD_LEN(x)		(((x) & 0xffff) << 16)

// pre: tx_packet must be at least five bytes long
static void test_xmit(OpenEthState *s, const uint8_t tx_packet[], size_t len, hwaddr desc_addr)
{
    assert(4 < len);

    uint64_t desc;
    desc = (uint32_t) (uintptr_t) tx_packet;
    desc <<= 32;
    desc |= TX_BD_LEN(len);
    desc |= TXD_RD | TXD_IRQ;

    open_eth_desc_write(s, desc_addr, desc);
}

static void test_tx(void)
{
    const unsigned TX_PACKET_COUNT = 3;

    const uint64_t tx_bd_num = 0x40;
    hwaddr desc_addr;

    /* each packet must be at least five bytes long */
    const uint8_t tx_packets[][5] =
                                    {{ 0x10U, 0x11U, 0x12U, 0x13U, 0x14U },
                                     { 0x20U, 0x21U, 0x22U, 0x23U, 0x24U },
                                     { 0x30U, 0x31U, 0x32U, 0x33U, 0x34U }};

    assert(sizeof(tx_packets)/5 == TX_PACKET_COUNT);

    assert(sizeof(tx_packets[0]) > 4);
    assert(sizeof(tx_packets[1]) > 4);
    assert(sizeof(tx_packets[2]) > 4);

    OpenEthState *s = OPEN_ETH_STATE(nc);

    /* reset MAC and MII */
    open_eth_reg_write(s, open_eth_reg(MODER), MODER_RST);
    assert(tx_bd_num == open_eth_reg_read(s, open_eth_reg(TX_BD_NUM)));

    /* setup MAC address */
    open_eth_reg_write(s, open_eth_reg(MAC_ADDR0), 0x56789ABC);
    open_eth_reg_write(s, open_eth_reg(MAC_ADDR1), 0x1234);

    /* enable IRQ for outgoing packets */
    open_eth_reg_write(s, open_eth_reg(INT_MASK), INT_MASK_TXB_M);

    /* setup address map to allow 32 bit hardware addresses */
    cpu_physical_memory_init((uintptr_t) tx_packets);

    /* enable transmitter such that it fires TX interrupts */
    open_eth_reg_write(s, open_eth_reg(MODER), MODER_TXEN);

    /* start at lowest tx buffer descriptor address */
    desc_addr = 0;

    raised_irq_count = 0;

    int k;
    for (k = 0; k < TX_PACKET_COUNT; k++) {
      __CPROVER_ASYNC_1: test_xmit(s, tx_packets[k], sizeof(tx_packets[k]), desc_addr);

      /* each buffer descriptor is eight bytes long */
      desc_addr += 8;
    }

    /* Wait until all spawned quasi-threads -- i.e. test_xmit() and
     * ethoc_start_xmit() -- have terminated.
     */
    __CPROVER_WAIT:

    /* 
     * The interrupt was only raised by the first TX frame because
     * our test interrupt handler does not clear any interrupt sources.
     * Thus, subsequent transmissions do not trigger the interrupt again.
     */
    assert(raised_irq_count == 1);

    /*
     * We do not model transmission errors; every TX frame eventually arrives.
     */ 
    assert(atomic_peer_rx_count() == 3);
}

// Since at most one handler can execute at the same time, raised_irq_count
// is not protected by a lock.
static irqreturn_t rx_handler(void *opaque, int n, int level)
{
    assert(n == 3);
    raised_irq_count++;

    return IRQ_HANDLED;
}

static int nc_open_eth_can_receive(NetClientState *nc)
{
    return open_eth_can_receive(OPEN_ETH_STATE(nc));
}

static ssize_t nc_open_eth_receive(NetClientState *nc,
                                     const uint8_t *buf, size_t size)
{
    return open_eth_receive(OPEN_ETH_STATE(nc), buf, size);
}

static void nc_open_eth_set_link_status(NetClientState *nc)
{
    OpenEthState *s = OPEN_ETH_STATE(nc);
    open_eth_set_link_status(s, s->nic->nc.link_down);
}

void main(void)
{
    /* Implementation of basic Net API */
    NetClientInfo nc_info;
    nc_info.can_receive = nc_open_eth_can_receive;
    nc_info.receive = nc_open_eth_receive;
    nc_info.link_status_changed = nc_open_eth_set_link_status;

    NetClientInfo peer_nc_info;
    peer_nc_info.can_receive = NULL;
    peer_nc_info.receive = peer_nc_open_eth_receive;
    peer_nc_info.link_status_changed = peer_nc_open_eth_set_link_status;

    /* Endpoint where packets are sent */
    atomic_reset_peer_rx_count();

    NetClientState peer;
    peer.info = &peer_nc_info;
    peer.link_down = 0;
    peer.peer = NULL;
    peer.receive_disabled = 0;

    /* NIC which can receive and transmit packets */
    NICState nic;
    nic.nc.info = &nc_info;
    nic.nc.link_down = 0;
    nic.nc.peer = &peer;
    nic.nc.receive_disabled = 0;

    /* Interrupt handler for incoming packets */
    IRQState irq;
    irq.n = 3;
    irq.handler = rx_handler;

    /* Ethernet MAC hardware model */
    OpenEthState eth;
    eth.nic = &nic;
    eth.irq = &irq;
    eth.mii.link_ok = true;

    memset(eth.mii.regs, 0, sizeof(eth.mii.regs));
    memset(eth.regs, 0, sizeof(eth.regs));
    memset(eth.desc, 0, sizeof(eth.desc));

    nic.opaque = &eth;
    nc = &nic.nc;

    /*
     * test_init();
     * test_rx();
     */

    test_init();
    test_tx();
}

