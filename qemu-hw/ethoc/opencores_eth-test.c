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
    assert(__OPENETH_DESC_SIZE__/2 == open_eth_reg_read(s, open_eth_reg(TX_BD_NUM)));
    assert(0x64 == open_eth_reg_read(s, open_eth_reg(MIIMODER)));
}

static bool raised_irq;

static void test_rx(void)
{
    const uint64_t tx_bd_num = __OPENETH_DESC_SIZE__/2;
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
    raised_irq = false;
    open_eth_receive(s, tx_packet, sizeof(tx_packet));

    /* validate DMA buffer content and IRQ */
    assert(sizeof(tx_packet) == sizeof(rx_packet));
#if 0
    assert((uint8_t*)(s->desc[tx_bd_num].buf_ptr)==rx_packet);
    assert(rx_packet[0]==0x12);
    assert(memcmp(tx_packet, rx_packet, sizeof(tx_packet)) == 0);
#endif
    assert((open_eth_reg_read(s, open_eth_reg(INT_SOURCE)) & INT_SOURCE_BUSY) == 0);
    assert(raised_irq == true);
}

static void test_rx_busy(void)
{
    const uint64_t tx_bd_num = __OPENETH_DESC_SIZE__-1;
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

    /* allocate only one RX buffer descriptor */
    open_eth_reg_write(s, open_eth_reg(TX_BD_NUM), tx_bd_num);

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

    /* enable receiver and unmask BUSY interrupt */
    open_eth_reg_write(s, open_eth_reg(MODER), MODER_RXEN);

    /* trigger DMA operations */
    open_eth_receive(s, tx_packet, sizeof(tx_packet));
    assert((open_eth_reg_read(s, open_eth_reg(INT_SOURCE)) & INT_SOURCE_BUSY) == 0);
    open_eth_receive(s, tx_packet, sizeof(tx_packet));
    assert((open_eth_reg_read(s, open_eth_reg(INT_SOURCE)) & INT_SOURCE_BUSY) == INT_SOURCE_BUSY);
}

static irqreturn_t rx_handler(void *opaque, int n, int level)
{
    assert(n == 3);
    raised_irq = true;

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

    /* NIC which can receive but not transmit packets */
    NICState nic;
    nic.nc.info = &nc_info;
    nic.nc.link_down = 0;
    nic.nc.peer = NULL;
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

    //memset(eth.mii.regs, 0, sizeof(eth.mii.regs));
    eth.mii.regs[MII_BMCR]=0;
    eth.mii.regs[MII_BMSR]=0;
    eth.mii.regs[MII_PHYIDR1]=0;
    eth.mii.regs[MII_PHYIDR2]=0;
    eth.mii.regs[MII_ANAR]=0;
    eth.mii.regs[MII_ANLPAR]=0;
    //memset(eth.regs, 0, sizeof(eth.regs));
    eth.regs[MODER]=0;
    eth.regs[INT_SOURCE]=0;
    eth.regs[INT_MASK]=0;
    eth.regs[IPGT]=0;
    eth.regs[IPGR1]=0;
    eth.regs[IPGR2]=0;
    eth.regs[PACKETLEN]=0;
    eth.regs[COLLCONF]=0;
    eth.regs[TX_BD_NUM]=0;
    eth.regs[CTRLMODER]=0;
    eth.regs[MIIMODER]=0;
    eth.regs[MIICOMMAND]=0;
    eth.regs[MIIADDRESS]=0;
    eth.regs[MIITX_DATA]=0;
    eth.regs[MIIRX_DATA]=0;
    eth.regs[MIISTATUS]=0;
    eth.regs[MAC_ADDR0]=0;
    eth.regs[MAC_ADDR1]=0;
    eth.regs[HASH0]=0;
    eth.regs[HASH1]=0;
    eth.regs[TXCTRL]=0;
    //memset(eth.desc, 0, sizeof(eth.desc));
    eth.desc[0].buf_ptr=0;
    eth.desc[1].buf_ptr=0;
    eth.desc[2].buf_ptr=0;
    eth.desc[3].buf_ptr=0;
    eth.desc[4].buf_ptr=0;
    eth.desc[5].buf_ptr=0;
    eth.desc[6].buf_ptr=0;
    eth.desc[7].buf_ptr=0;
    eth.desc[0].len_flags=0;
    eth.desc[1].len_flags=0;
    eth.desc[2].len_flags=0;
    eth.desc[3].len_flags=0;
    eth.desc[4].len_flags=0;
    eth.desc[5].len_flags=0;
    eth.desc[6].len_flags=0;
    eth.desc[7].len_flags=0;

    nic.opaque = &eth;
    nc = &nic.nc;

#ifdef ETHOC_BENCHMARK_PROP_2
    test_init();
#endif
#ifdef ETHOC_BENCHMARK_PROP_3
    test_rx();
#endif
#ifdef ETHOC_BENCHMARK_PROP_4
    test_rx_busy();
#endif
}

