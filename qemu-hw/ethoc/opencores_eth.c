/*
 * OpenCores Ethernet MAC 10/100 with a subset of
 * National Semiconductors DP83848C 10/100 PHY
 *
 * Browse the data sheet:
 *
 *    http://opencores.org/project,ethmac
 *    http://www.ti.com/lit/ds/symlink/dp83848c.pdf
 *
 * Copyright (C) 2012 Alex Horn <alex.horn@cs.ox.ac.uk>
 * Copyright (C) 2011-2012 Max Filippov <jcmvbkbc@gmail.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later. See the COPYING file in the top-level directory.
 */
#include "opencores_eth.h"
#include "sys.h"
#include "cpu.h"
#include "assert.h"

#ifdef CONCRETE_EXECUTION
#include "trace.h"
#endif

/* RECSMALL is not used because it breaks tap networking in linux:
 * incoming ARP responses are too short
 */
#undef USE_RECSMALL

#define GET_FIELD(v, field) (((v) & (field)) >> (field ## _LBN))
#define GET_REGBIT(s, reg, field) ((s)->regs[reg] & (reg ## _ ## field))
#define GET_REGFIELD(s, reg, field) \
    GET_FIELD((s)->regs[reg], reg ## _ ## field)

#define SET_FIELD(v, field, data) \
    ((v) = (((v) & ~(field)) | (((data) << (field ## _LBN)) & (field))))
#define SET_REGFIELD(s, reg, field, data) \
    SET_FIELD((s)->regs[reg], reg ## _ ## field, data)

#ifndef ATOMIC_FN
#define ATOMIC_FN(f) __VERIFIER_atomic_##f
#endif

#define DECL_DEF_ATOMIC1(r, f, t1, a1) \
  r f(t1 a1); \
  inline r ATOMIC_FN(f)(t1 a1) \
  { \
    return f(a1); \
  }

#define DECL_DEF_ATOMIC2(r, f, t1, a1, t2, a2) \
  r f(t1 a1, t2 a2); \
  inline r ATOMIC_FN(f)(t1 a1, t2 a2) \
  { \
    return f(a1, a2); \
  }

#define DECL_DEF_ATOMIC3(r, f, t1, a1, t2, a2, t3, a3) \
  r f(t1 a1, t2 a2, t3 a3); \
  inline r ATOMIC_FN(f)(t1 a1, t2 a2, t3 a3) \
  { \
    return f(a1, a2, a3); \
  }

#define DECL_DEF_ATOMIC_void1(f, t1, a1) \
  void f(t1 a1); \
  inline void ATOMIC_FN(f)(t1 a1) \
  { \
    f(a1); \
  }

#define DECL_DEF_ATOMIC_void2(f, t1, a1, t2, a2) \
  void f(t1 a1, t2 a2); \
  inline void ATOMIC_FN(f)(t1 a1, t2 a2) \
  { \
    f(a1, a2); \
  }

#define DECL_DEF_ATOMIC_void3(f, t1, a1, t2, a2, t3, a3) \
  void f(t1 a1, t2 a2, t3 a3); \
  inline void ATOMIC_FN(f)(t1 a1, t2 a2, t3 a3) \
  { \
    f(a1, a2, a3); \
  }

/**
 * open_eth_reg_read:
 * @s: self object pointer
 * @addr: address of register
 *
 * Returns the content of a register.
 *
 * @see_also: Chapter 3 in data sheet
 * @see_also: open_eth_reg()
 */
DECL_DEF_ATOMIC2(uint32_t, open_eth_reg_read, OpenEthState *, s, hwaddr, addr)

/**
 * open_eth_reg_write:
 * @s: self object pointer
 * @addr: address of register
 * @val: double word to be written
 *
 * Overwrites the content of a register with the given value.
 *
 * Note that certain register values (e.g. @TX_BD_NUM) should only be changed
 * when the @MODER_TXEN and @MODER_RXEN bits are both disabled. The new value
 * could also be subject to range restrictions. For example, @TX_BD_NUM should
 * never be greater than 0x80h.
 *
 * @see_also: Chapter 3 in data sheet
 * @see_also: open_eth_reg()
 */
DECL_DEF_ATOMIC_void3(open_eth_reg_write, OpenEthState *, s, hwaddr, addr, uint32_t, val)

/**
 * open_eth_desc_read:
 * @s: self object pointer
 * @addr: address of descriptor starting at zero
 *
 * Returns a single buffer descriptor out of a maximum of 128 possible ones.
 * The register indexed by @TX_BD_NUM determines the address boundary between
 * transmission and reception buffer descriptors. That is, every TX BD address
 * must be strictly less than @TX_BD_NUM whereas every RX BD address must be
 * greater or equal to @TX_BD_NUM.
 *
 * @see_also: Section 4.2.2 in data sheet
 */
DECL_DEF_ATOMIC2(uint64_t, open_eth_desc_read, OpenEthState *, s, hwaddr, addr)

/**
 * open_eth_desc_write:
 * @s: self object pointer
 * @addr: address of descriptor starting at zero
 * @val: double word to be written
 *
 * Overwrites a buffer descriptor. Each descriptor is 64 bits wide.
 * There are at most 128 such descriptors. The register indexed by
 * @TX_BD_NUM should hold the actual number of used descriptors.
 * The lower 32 bits hold the buffer descriptor's status whereas the
 * upper 32 bits hold a DMA address.
 *
 * @see_also: Section 4.2.2 in data sheet
 */
DECL_DEF_ATOMIC_void3(open_eth_desc_write, OpenEthState *, s, hwaddr, addr, uint64_t, val)

/**
 * open_eth_can_receive:
 * @s: self object pointer
 *
 * May the open_eth_receive(@s) function be called?
 */
DECL_DEF_ATOMIC1(int, open_eth_can_receive, OpenEthState *, s)

/**
 * open_eth_receive:
 * @s: self object pointer
 * @buf: bytes to be written
 * @size: maximum number of bytes to be written
 *
 * Writes at most @size bytes in the read-only @buf array to memory according
 * to the direct-memory address (DMA) in the current buffer descriptor.
 */
DECL_DEF_ATOMIC3(ssize_t, open_eth_receive, OpenEthState *, s, const uint8_t *, buf, size_t, size)

/**
 * open_eth_set_link_status:
 * @s: self object pointer
 * @link_down: flag to be written
 *
 * Update net client's link status.
 */
DECL_DEF_ATOMIC_void2(open_eth_set_link_status, OpenEthState *, s, bool, link_down)



static void mii_set_link(Mii *s, bool link_ok)
{
    if (link_ok) {
        s->regs[MII_BMSR] |= 0x4;
        s->regs[MII_ANLPAR] |= 0x01e1;
    } else {
        s->regs[MII_BMSR] &= ~0x4;
        s->regs[MII_ANLPAR] &= 0x01ff;
    }
    s->link_ok = link_ok;
}

static void mii_reset(Mii *s)
{
    memset(s->regs, 0, sizeof(s->regs));
    s->regs[MII_BMCR] = 0x1000;
    s->regs[MII_BMSR] = 0x7848; /* no ext regs */
    s->regs[MII_PHYIDR1] = 0x2000;
    s->regs[MII_PHYIDR2] = 0x5c90;
    s->regs[MII_ANAR] = 0x01e1;
    mii_set_link(s, s->link_ok);
}

static void mii_ro(Mii *s, uint16_t v)
{
}

static void mii_write_bmcr(Mii *s, uint16_t v)
{
    if (v & 0x8000) {
        mii_reset(s);
    } else {
        s->regs[MII_BMCR] = v;
    }
}

static void mii_write_host(Mii *s, unsigned idx, uint16_t v)
{
    static void (*reg_write[MII_REG_MAX])(Mii *s, uint16_t v) = {
        [MII_BMCR] = mii_write_bmcr,
        [MII_BMSR] = mii_ro,
        [MII_PHYIDR1] = mii_ro,
        [MII_PHYIDR2] = mii_ro,
    };

    if (idx < MII_REG_MAX) {
#ifdef CONCRETE_EXECUTION
        trace_open_eth_mii_write(idx, v);
#endif
        if (reg_write[idx]) {
            reg_write[idx](s, v);
        } else {
            s->regs[idx] = v;
        }
    }
}

static uint16_t mii_read_host(Mii *s, unsigned idx)
{
#ifdef CONCRETE_EXECUTION
    trace_open_eth_mii_read(idx, s->regs[idx]);
#endif
    return s->regs[idx];
}

static inline uint64_t get_desc_at(OpenEthState *s, hwaddr addr)
{
    addr &= 0x3ff;
    return *((uint64_t *)((uint8_t *)s->desc + addr));
}

static inline void set_desc_at(OpenEthState *s, hwaddr addr, uint64_t val)
{
    addr &= 0x3ff;
    *((uint64_t *)((uint8_t *)s->desc + addr)) = val;
}

static open_eth_desc *rx_desc(OpenEthState *s)
{
    return (open_eth_desc*)s->desc + s->rx_desc;
}

static open_eth_desc *tx_desc(OpenEthState *s)
{
    return (open_eth_desc*)s->desc + s->tx_desc;
}

static void open_eth_update_irq(OpenEthState *s,
        uint32_t old, uint32_t new)
{
    if (!old != !new) {
#ifdef CONCRETE_EXECUTION
        trace_open_eth_update_irq(new);
#endif
        hw_set_irq(s->irq, new);
    }
}

static void open_eth_int_source_write(OpenEthState *s,
        uint32_t val)
{
    uint32_t old_val = s->regs[INT_SOURCE];

    s->regs[INT_SOURCE] = val;
    open_eth_update_irq(s, old_val & s->regs[INT_MASK],
            s->regs[INT_SOURCE] & s->regs[INT_MASK]);
}

void open_eth_set_link_status(OpenEthState *s, bool link_down)
{
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_begin();
#endif
#endif
    if (GET_REGBIT(s, MIICOMMAND, SCANSTAT)) {
        SET_REGFIELD(s, MIISTATUS, LINKFAIL, link_down);
    }
    mii_set_link(&s->mii, !link_down);
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_end();
#endif
#endif
}

static void open_eth_reset(OpenEthState *s)
{
    memset(s->regs, 0, sizeof(s->regs));
    s->regs[MODER] = 0xa000;
    s->regs[IPGT] = 0x12;
    s->regs[IPGR1] = 0xc;
    s->regs[IPGR2] = 0x12;
    s->regs[PACKETLEN] = 0x400600;
    s->regs[COLLCONF] = 0xf003f;
    s->regs[TX_BD_NUM] = __OPENETH_DESC_SIZE__ / 2;
    s->regs[MIIMODER] = 0x64;

    s->tx_desc = 0;
    s->rx_desc = __OPENETH_DESC_SIZE__ / 2;

    mii_reset(&s->mii);
    open_eth_set_link_status(s, s->nic->nc.link_down);
}

int open_eth_can_receive(OpenEthState *s)
{
    //__CPROVER_atomic_begin();
    int val = GET_REGBIT(s, MODER, RXEN) &&
        (s->regs[TX_BD_NUM] < __OPENETH_DESC_SIZE__) &&
        (rx_desc(s)->len_flags & RXD_E);
    //__CPROVER_atomic_end();
    return val;
}

ssize_t open_eth_receive(OpenEthState *s, const uint8_t *buf, size_t size)
{
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_begin();
#endif
#endif
    if (!GET_REGBIT(s, MODER, RXEN) || (s->regs[TX_BD_NUM] >= __OPENETH_DESC_SIZE__)) {
       size=0;
       goto out;
    }

    size_t maxfl = GET_REGFIELD(s, PACKETLEN, MAXFL);
    size_t minfl = GET_REGFIELD(s, PACKETLEN, MINFL);
    size_t fcsl = 4;
    bool miss = true;

#ifdef CONCRETE_EXECUTION
    trace_open_eth_receive((unsigned)size);
#endif
    if (size >= 6) {
        static const uint8_t bcast_addr[] = {
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff
        };
        if (memcmp(buf, bcast_addr, sizeof(bcast_addr)) == 0) {
            miss = GET_REGBIT(s, MODER, BRO);
        } else if ((buf[0] & 0x1) || GET_REGBIT(s, MODER, IAM)) {
            unsigned mcast_idx = compute_mcast_idx(buf);
            miss = !(s->regs[HASH0 + mcast_idx / 32] &
                    (1 << (mcast_idx % 32)));
#ifdef CONCRETE_EXECUTION
           trace_open_eth_receive_mcast(
                    mcast_idx, s->regs[HASH0], s->regs[HASH1]);
#endif
        } else {
            miss = GET_REGFIELD(s, MAC_ADDR1, BYTE0) != buf[0] ||
                GET_REGFIELD(s, MAC_ADDR1, BYTE1) != buf[1] ||
                GET_REGFIELD(s, MAC_ADDR0, BYTE2) != buf[2] ||
                GET_REGFIELD(s, MAC_ADDR0, BYTE3) != buf[3] ||
                GET_REGFIELD(s, MAC_ADDR0, BYTE4) != buf[4] ||
                GET_REGFIELD(s, MAC_ADDR0, BYTE5) != buf[5];
        }
    }

    if (miss && !GET_REGBIT(s, MODER, PRO)) {
#ifdef CONCRETE_EXECUTION
        trace_open_eth_receive_reject();
#endif
        goto out;
    }

#ifdef USE_RECSMALL
    if (GET_REGBIT(s, MODER, RECSMALL) || size >= minfl) {
#else
    {
#endif
        static const uint8_t zero[64] = {0};
        open_eth_desc *desc = rx_desc(s);

        if ((desc->len_flags & RXD_E) == 0) {
            /* As long as the RX buffer descriptor
             * is empty, it won't be used.
             */
            open_eth_int_source_write(s,
                        s->regs[INT_SOURCE] | INT_SOURCE_BUSY);
            size=0;
            goto out;
        }

        size_t copy_size = GET_REGBIT(s, MODER, HUGEN) ? 65536 : maxfl;

        desc->len_flags &= ~(RXD_CF | RXD_M | RXD_OR |
                RXD_IS | RXD_DN | RXD_TL | RXD_SF | RXD_CRC | RXD_LC);

        if (copy_size > size) {
            copy_size = size;
        } else {
            fcsl = 0;
        }
        if (miss) {
            desc->len_flags |= RXD_M;
        }
        if (GET_REGBIT(s, MODER, HUGEN) && size > maxfl) {
            desc->len_flags |= RXD_TL;
        }
#ifdef USE_RECSMALL
        if (size < minfl) {
            desc->len_flags |= RXD_SF;
        }
#endif

        cpu_physical_memory_write(desc->buf_ptr, buf, copy_size);

        if (GET_REGBIT(s, MODER, PAD) && copy_size < minfl) {
            if (minfl - copy_size > fcsl) {
                fcsl = 0;
            } else {
                fcsl -= minfl - copy_size;
            }
            while (copy_size < minfl) {
                size_t zero_sz = minfl - copy_size < sizeof(zero) ?
                    minfl - copy_size : sizeof(zero);

                cpu_physical_memory_write(desc->buf_ptr + copy_size,
                        zero, zero_sz);
                copy_size += zero_sz;
            }
        }

        /* There's no FCS in the frames handed to us by the QEMU, zero fill it.
         * Don't do it if the frame is cut at the MAXFL or padded with 4 or
         * more bytes to the MINFL.
         */
        cpu_physical_memory_write(desc->buf_ptr + copy_size, zero, fcsl);
        copy_size += fcsl;

        SET_FIELD(desc->len_flags, RXD_LEN, copy_size);

        if ((desc->len_flags & RXD_WRAP) || s->rx_desc == (__OPENETH_DESC_SIZE__-1)) {
            s->rx_desc = s->regs[TX_BD_NUM];
        } else {
            ++s->rx_desc;
        }
        desc->len_flags &= ~RXD_E;
#ifdef CONCRETE_EXECUTION
        trace_open_eth_receive_desc(desc->buf_ptr, desc->len_flags);
#endif
        if (desc->len_flags & RXD_IRQ) {
            open_eth_int_source_write(s,
                    s->regs[INT_SOURCE] | INT_SOURCE_RXB);
        }
    }
out:
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_end();
#endif
#endif
    return size;
}

static void open_eth_start_xmit(OpenEthState *s, open_eth_desc *tx)
{
    uint8_t buf[16];
    unsigned len = GET_FIELD(tx->len_flags, TXD_LEN);
    unsigned tx_len = len;

    if ((tx->len_flags & TXD_PAD) &&
            tx_len < GET_REGFIELD(s, PACKETLEN, MINFL)) {
        tx_len = GET_REGFIELD(s, PACKETLEN, MINFL);
    }
    if (!GET_REGBIT(s, MODER, HUGEN) &&
            tx_len > GET_REGFIELD(s, PACKETLEN, MAXFL)) {
        tx_len = GET_REGFIELD(s, PACKETLEN, MAXFL);
    }
#ifdef CONCRETE_EXECUTION
    trace_open_eth_start_xmit(tx->buf_ptr, len, tx_len);
#endif

    if (len > tx_len) {
        len = tx_len;
    }
    cpu_physical_memory_read(tx->buf_ptr, buf, len);
    if (tx_len > len) {
        memset(buf + len, 0, tx_len - len);
    }
    send_packet(&s->nic->nc, buf, tx_len);

    if (tx->len_flags & TXD_WR) {
        s->tx_desc = 0;
    } else {
        ++s->tx_desc;
        if (s->tx_desc >= s->regs[TX_BD_NUM]) {
            s->tx_desc = 0;
        }
    }
    tx->len_flags &= ~(TXD_RD | TXD_UR |
            TXD_RTRY | TXD_RL | TXD_LC | TXD_DF | TXD_CS);
    if (tx->len_flags & TXD_IRQ) {
        open_eth_int_source_write(s, s->regs[INT_SOURCE] | INT_SOURCE_TXB);
    }

}

static void open_eth_check_start_xmit(OpenEthState *s)
{
    open_eth_desc *tx = tx_desc(s);
    if (GET_REGBIT(s, MODER, TXEN) && s->regs[TX_BD_NUM] > 0 &&
            (tx->len_flags & TXD_RD) &&
            GET_FIELD(tx->len_flags, TXD_LEN) > 4) {
        open_eth_start_xmit(s, tx);
    }
}

uint32_t open_eth_reg_read(OpenEthState *s, hwaddr addr)
{
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_begin();
#endif
#endif
    static uint32_t (*reg_read[REG_MAX])(OpenEthState *s) = {
    };
    unsigned idx = addr / 4;
    uint32_t val = 0;

    if (idx < REG_MAX) {
        if (reg_read[idx]) {
            val = reg_read[idx](s);
        } else {
            val = s->regs[idx];
        }
    }
#ifdef CONCRETE_EXECUTION
    trace_open_eth_reg_read((uint32_t)addr, val);
#endif
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_end();
#endif
#endif
    return val;
}

static void open_eth_ro(OpenEthState *s, uint32_t val)
{
}

static void open_eth_moder_host_write(OpenEthState *s, uint32_t val)
{
    uint32_t set = val & ~s->regs[MODER];

    if (set & MODER_RST) {
        open_eth_reset(s);
    }

    s->regs[MODER] = val;

    if (set & MODER_RXEN) {
        s->rx_desc = s->regs[TX_BD_NUM];

	/* VC: When the receiver is being enabled, there must
 	 *     exist at least one empty RX buffer descriptor.
 	 */ 
#ifdef ETHOC_BENCHMARK_PROP_1
	assert(open_eth_can_receive(s));
#endif
    }
    if (set & MODER_TXEN) {
        s->tx_desc = 0;
        open_eth_check_start_xmit(s);
    }
}

static void open_eth_int_source_host_write(OpenEthState *s, uint32_t val)
{
    uint32_t old = s->regs[INT_SOURCE];

    s->regs[INT_SOURCE] &= ~val;
    open_eth_update_irq(s, old & s->regs[INT_MASK],
            s->regs[INT_SOURCE] & s->regs[INT_MASK]);
}

static void open_eth_int_mask_host_write(OpenEthState *s, uint32_t val)
{
    uint32_t old = s->regs[INT_MASK];

    s->regs[INT_MASK] = val;

/* Changing the INT_MASK register does not trigger an interrupt according
 * to the OpenCores Ethernet MAC data sheet, as explained next.
 *
 * The function call below originates from the QEMU OpenCores Ethernet MAC
 * hardware model. It causes the interrupt handler to be called. The interrupt
 * handler, in turn, must read the INT_SOURCE register to determine the cause
 * of the interrupt. Section 3.2 in the data sheet (p. 10) lists the seven
 * possibilities why the interrupt was raised. None of these would allow the
 * interrupt handler to determine that the interrupt is caused by a change to
 * the INT_MASK register. This suggests that this feature is specific to QEMU.
 * Thus, we remove this functionality from the analysis with CBMC because
 * we are only interested in features that can be justified by the data sheet.
 */
#ifndef _CBMC_
    open_eth_update_irq(s, s->regs[INT_SOURCE] & old,
            s->regs[INT_SOURCE] & s->regs[INT_MASK]);
#endif
}

static void open_eth_mii_command_host_write(OpenEthState *s, uint32_t val)
{
    unsigned fiad = GET_REGFIELD(s, MIIADDRESS, FIAD);
    unsigned rgad = GET_REGFIELD(s, MIIADDRESS, RGAD);

    if (val & MIICOMMAND_WCTRLDATA) {
        if (fiad == DEFAULT_PHY) {
            mii_write_host(&s->mii, rgad,
                    GET_REGFIELD(s, MIITX_DATA, CTRLDATA));
        }
    }
    if (val & MIICOMMAND_RSTAT) {
        if (fiad == DEFAULT_PHY) {
            SET_REGFIELD(s, MIIRX_DATA, PRSD,
                    mii_read_host(&s->mii, rgad));
        } else {
            s->regs[MIIRX_DATA] = 0xffff;
        }
        SET_REGFIELD(s, MIISTATUS, LINKFAIL, s->nic->nc.link_down);
    }
}

static void open_eth_mii_tx_host_write(OpenEthState *s, uint32_t val)
{
    SET_REGFIELD(s, MIITX_DATA, CTRLDATA, val);
    if (GET_REGFIELD(s, MIIADDRESS, FIAD) == DEFAULT_PHY) {
        mii_write_host(&s->mii, GET_REGFIELD(s, MIIADDRESS, RGAD),
                GET_REGFIELD(s, MIITX_DATA, CTRLDATA));
    }
}

void open_eth_reg_write(OpenEthState *s, hwaddr addr, uint32_t val)
{
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_begin();
#endif
#endif
    static void (*reg_write[REG_MAX])(OpenEthState *s, uint32_t val) = {
        [MODER] = open_eth_moder_host_write,
        [INT_SOURCE] = open_eth_int_source_host_write,
        [INT_MASK] = open_eth_int_mask_host_write,
        [MIICOMMAND] = open_eth_mii_command_host_write,
        [MIITX_DATA] = open_eth_mii_tx_host_write,
        [MIISTATUS] = open_eth_ro,
    };
    unsigned idx = addr / 4;

    if (idx < REG_MAX) {
#ifdef CONCRETE_EXECUTION
        trace_open_eth_reg_write((uint32_t)addr, val);
#endif
        if (reg_write[idx]) {
            reg_write[idx](s, val);
        } else {
            s->regs[idx] = val;
        }
    }
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_end();
#endif
#endif
}

uint64_t open_eth_desc_read(OpenEthState *s, hwaddr addr)
{
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_begin();
#endif
#endif
    uint64_t v;

    v = get_desc_at(s, addr);
#ifdef CONCRETE_EXECUTION
    trace_open_eth_desc_read((uint32_t)addr, (uint32_t)v);
#endif
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_end();
#endif
#endif
    return v;

}

void open_eth_desc_write(OpenEthState *s, hwaddr addr, uint64_t val)
{
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_begin();
#endif
#endif
#ifdef CONCRETE_EXECUTION
    trace_open_eth_desc_write((uint32_t)addr, (uint32_t)val);
#endif
    set_desc_at(s, addr, val);

    open_eth_check_start_xmit(s);
#ifdef _CBMC_
#ifndef _NO_CBMC_ATOMIC_
    __CPROVER_atomic_end();
#endif
#endif
}

