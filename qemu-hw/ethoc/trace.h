/* Debug and tracer functions for OpenCores Ethernet MAC controller. */
#ifndef OPENCORES_ETH_TRACE_H
#define OPENCORES_ETH_TRACE_H

#include <stdint.h>
#include <stdio.h>

static void trace_open_eth_mii_write(unsigned idx, uint16_t v)
{
    printf("MII[%02x] <- %04x\n", idx, v);
}

static void trace_open_eth_mii_read(unsigned idx, uint16_t v)
{
    printf("MII[%02x] -> %04x\n", idx, v);
}

static void trace_open_eth_update_irq(uint32_t v)
{
    printf("IRQ <- %x\n", v);
}

static void trace_open_eth_receive(unsigned len)
{
    printf("RX: len: %u\n", len);
}

static void trace_open_eth_receive_mcast(unsigned idx, uint32_t h0, uint32_t h1)
{
    printf("MCAST: idx = %u, hash: %08x:%08x\n", idx, h0, h1);
}

static void trace_open_eth_receive_reject(void)
{
    printf("RX: rejected\n");
}

static void trace_open_eth_receive_desc(uint32_t addr, uint32_t len_flags)
{
    printf("RX: %08x, len_flags: %08x\n", addr, len_flags);
}

static void trace_open_eth_start_xmit(uint32_t addr, unsigned len, unsigned tx_len)
{
    printf("TX: %08x, len: %u, tx_len: %u\n", addr, len, tx_len);
}

static void trace_open_eth_reg_read(uint32_t addr, uint32_t v)
{
    printf("MAC[%02x] -> %08x\n", addr, v);
}

static void trace_open_eth_reg_write(uint32_t addr, uint32_t v)
{
    printf("MAC[%02x] <- %08x\n", addr, v);
}

static void trace_open_eth_desc_read(uint32_t addr, uint32_t v)
{
    printf("DESC[%04x] -> %08x\n", addr, v);
}

static void trace_open_eth_desc_write(uint32_t addr, uint32_t v)
{
    printf("DESC[%04x] <- %08x\n", addr, v);
}

#endif
