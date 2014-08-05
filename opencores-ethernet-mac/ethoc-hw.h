/*
 * Hardware model of OpenCores Ethernet MAC 10/100 with a
 * subset of National Semiconductors DP83848C 10/100 PHY
 *
 * Browse the data sheets:
 *
 *    http://opencores.org/project,ethmac
 *    http://www.ti.com/lit/gpn/dp83848c
 *
 * Copyright (C) 2012 Alex Horn <alex.horn@cs.ox.ac.uk>
 * Copyright (C) 2011-2012 Max Filippov <jcmvbkbc@gmail.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later. See the COPYING file in the top-level directory.
 */
#ifndef _ETHOC_HW_H_
#define _ETHOC_HW_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "hwaddr.h"

/*
 * Fall back to POSIX threads
 */
#ifndef _CBMC_
#include <pthread.h>
#endif

/**
 * Generic IRQ/GPIO pin infrastructure. 
 *
 * enum irqreturn:
 * @IRQ_NONE		interrupt was not from this device
 * @IRQ_HANDLED		interrupt was handled by this device
 * @IRQ_WAKE_THREAD	handler requests to wake the handler thread
 */
enum irqreturn {
	IRQ_NONE		= (0 << 0),
	IRQ_HANDLED		= (1 << 0),
	IRQ_WAKE_THREAD		= (1 << 1),
};

typedef enum irqreturn irqreturn_t;
#define IRQ_RETVAL(x)	((x) != IRQ_NONE)

typedef irqreturn_t (*irq_handler)(void *opaque, int n, int level);

typedef struct IRQState *hw_irq;

typedef struct IRQState {
    irq_handler handler;
    void *opaque;
    int n;
} IRQState;

void hw_set_irq(hw_irq irq, int level);

/*
 * Forward declaration
 */
struct NICState;

/**
 * PHY identifier for MDIO setup
 */
#define DEFAULT_PHY 1

/**
 * DP83848C PHYTER MII registers
 *
 * @see_also: http://www.ti.com/lit/gpn/dp83848c
 */
enum {
    MII_BMCR,
    MII_BMSR,
    MII_PHYIDR1,
    MII_PHYIDR2,
    MII_ANAR,
    MII_ANLPAR,
    MII_REG_MAX = 16,
};

/**
 * Hardware model of DP83848C PHYTER MII
 */
typedef struct Mii {
    uint16_t regs[MII_REG_MAX];
    bool link_ok;
} Mii;

/**
 * OpenCores Ethernet MAC registers
 *
 * @see_also: http://opencores.org/project,ethmac
 * @see also: open_eth_reg()
 */
enum OpenEthReg {
    MODER,
    INT_SOURCE,
    INT_MASK,
    IPGT,
    IPGR1,
    IPGR2,
    PACKETLEN,
    COLLCONF,
    TX_BD_NUM,
    CTRLMODER,
    MIIMODER,
    MIICOMMAND,
    MIIADDRESS,
    MIITX_DATA,
    MIIRX_DATA,
    MIISTATUS,
    MAC_ADDR0,
    MAC_ADDR1,
    HASH0,
    HASH1,
    TXCTRL,
    REG_MAX,
};

/**
 * open_eth_reg:
 * @reg_ix: register index
 *
 * Returns hardware address of register index
 *
 * This hardware address can be used for @open_eth_reg_read() and
 * @open_eth_reg_write() calls.
 */
static inline hwaddr open_eth_reg(enum OpenEthReg reg_ix)
{
    return reg_ix * 4;
}

/**
 * Masks for MODER register in OpenCores Ethernet MAC
 *
 * @see_also: Section 3.1 in data sheet
 */
enum {
    MODER_RECSMALL = 0x10000,
    MODER_PAD = 0x8000,
    MODER_HUGEN = 0x4000,
    MODER_RST = 0x800, /* reserved */
    MODER_LOOPBCK = 0x80,
    MODER_PRO = 0x20,
    MODER_IAM = 0x10,
    MODER_BRO = 0x8,
    MODER_TXEN = 0x2,
    MODER_RXEN = 0x1,
};

/**
 * Masks for INT_SOURCE register in OpenCores Ethernet MAC
 *
 * Note that these are NOT interrupt masks (i.e. INT_MASK register).
 *
 * @see_also: Section 3.2 in data sheet
 */
enum {
    INT_SOURCE_BUSY = 0x10,
    INT_SOURCE_RXB = 0x4,
    INT_SOURCE_TXB = 0x1,
};

/**
 * Interrupt masks for OpenCores Ethernet MAC
 *
 * @see_also: Section 3.3 in data sheet
 */
enum {
    INT_MASK_TXB_M = 0x0,
    INT_MASK_TXE_M = 0x2,
    INT_MASK_RXF_M = 0x4,
    INT_MASK_RXE_M = 0x8,
    INT_MASK_BUSY_M = 0x10,
    INT_MASK_TXC_M = 0x20,
    INT_MASK_RXC_M = 0x40,
};

/**
 * Masks for PACKETLEN register in OpenCores Ethernet MAC
 *
 * @see_also: Section 3.7 in data sheet
 */
enum {
    PACKETLEN_MINFL = 0xffff0000,
    PACKETLEN_MINFL_LBN = 16,
    PACKETLEN_MAXFL = 0xffff,
    PACKETLEN_MAXFL_LBN = 0,
};

/**
 * Masks for MIICOMMAND register in OpenCores Ethernet MAC
 *
 * @see_also: Section 3.12 in data sheet
 */
enum {
    MIICOMMAND_WCTRLDATA = 0x4,
    MIICOMMAND_RSTAT = 0x2,
    MIICOMMAND_SCANSTAT = 0x1,
};

/**
 * Masks for MIIADDRESS register in OpenCores Ethernet MAC
 *
 * Each mask has an LBN which is a left offset from the least significant bit.
 * That is, an LBN equal to zero corresponds to the LSB (value 1).
 *
 * @see_also: Section 3.13 in data sheet
 */
enum {
    MIIADDRESS_RGAD = 0x1f00,
    MIIADDRESS_RGAD_LBN = 8,
    MIIADDRESS_FIAD = 0x1f,
    MIIADDRESS_FIAD_LBN = 0,
};

/**
 * Masks for MIITX_DATA register in OpenCores Ethernet MAC
 *
 * Each mask has an LBN which is a left offset from the least significant bit.
 * That is, an LBN equal to zero corresponds to the LSB (value 1).
 *
 * @see_also: Section 3.14 in data sheet
 */
enum {
    MIITX_DATA_CTRLDATA = 0xffff,
    MIITX_DATA_CTRLDATA_LBN = 0,
};

/**
 * Masks for MIIRX_DATA register in OpenCores Ethernet MAC
 *
 * Each mask has an LBN which is a left offset from the least significant bit.
 * That is, an LBN equal to zero corresponds to the LSB (value 1).
 *
 * @see_also: Section 3.15 in data sheet
 */
enum {
    MIIRX_DATA_PRSD = 0xffff,
    MIIRX_DATA_PRSD_LBN = 0,
};

/**
 * Masks for MIISTATUS_DATA register in OpenCores Ethernet MAC
 *
 * Each mask has an LBN which is a left offset from the least significant bit.
 * That is, an LBN equal to zero corresponds to the LSB (value 1).
 *
 * @see_also: Section 3.16 in data sheet
 */
enum {
    MIISTATUS_LINKFAIL = 0x1,
    MIISTATUS_LINKFAIL_LBN = 0,
};

/**
 * Masks for MAC_ADDR0 register in OpenCores Ethernet MAC
 *
 * Each mask has an LBN which is a left offset from the least significant bit.
 * That is, an LBN equal to zero corresponds to the LSB (value 1).
 *
 * @see_also: Section 3.17 in data sheet
 */
enum {
    MAC_ADDR0_BYTE2 = 0xff000000,
    MAC_ADDR0_BYTE2_LBN = 24,
    MAC_ADDR0_BYTE3 = 0xff0000,
    MAC_ADDR0_BYTE3_LBN = 16,
    MAC_ADDR0_BYTE4 = 0xff00,
    MAC_ADDR0_BYTE4_LBN = 8,
    MAC_ADDR0_BYTE5 = 0xff,
    MAC_ADDR0_BYTE5_LBN = 0,
};

/**
 * Masks for MAC_ADDR1 register in OpenCores Ethernet MAC
 *
 * Each mask has an LBN which is a left offset from the least significant bit.
 * That is, an LBN equal to zero corresponds to the LSB (value 1).
 *
 * @see_also: Section 3.18 in data sheet
 */
enum {
    MAC_ADDR1_BYTE0 = 0xff00,
    MAC_ADDR1_BYTE0_LBN = 8,
    MAC_ADDR1_BYTE1 = 0xff,
    MAC_ADDR1_BYTE1_LBN = 0,
};

/**
 * Masks for a single TX buffer descriptor in OpenCores Ethernet MAC
 *
 * Each mask has an LBN which is a left offset from the least significant bit.
 * That is, an LBN equal to zero corresponds to the LSB (value 1).
 *
 * @see_also: Section 4.2.2.1 in data sheet
 */
enum {
    TXD_LEN = 0xffff0000,
    TXD_LEN_LBN = 16,
    TXD_RD = 0x8000,
    TXD_IRQ = 0x4000,
    TXD_WR = 0x2000,
    TXD_PAD = 0x1000,
    TXD_CRC = 0x800,
    TXD_UR = 0x100,
    TXD_RTRY = 0xf0,
    TXD_RTRY_LBN = 4,
    TXD_RL = 0x8,
    TXD_LC = 0x4,
    TXD_DF = 0x2,
    TXD_CS = 0x1,
};

/**
 * Masks for a single RX buffer descriptor in OpenCores Ethernet MAC
 *
 * Each mask has an LBN which is a left offset from the least significant bit.
 * That is, an LBN equal to zero corresponds to the LSB (value 1).
 *
 * @see_also: Section 4.2.2.2 in data sheet
 */
enum {
    RXD_LEN = 0xffff0000,
    RXD_LEN_LBN = 16,
    RXD_E = 0x8000,
    RXD_IRQ = 0x4000,
    RXD_WRAP = 0x2000,
    RXD_CF = 0x100,
    RXD_M = 0x80,
    RXD_OR = 0x40,
    RXD_IS = 0x20,
    RXD_DN = 0x10,
    RXD_TL = 0x8,
    RXD_SF = 0x4,
    RXD_CRC = 0x2,
    RXD_LC = 0x1,
};

/**
 * Buffer descriptor
 */
typedef struct open_eth_desc {
    uint32_t len_flags;
    uint32_t buf_ptr;
} open_eth_desc;

/*
 * The size of the buffer descriptors was decreased from 128 to eight
 * to make the formal analysis with tools more feasible that do not
 * support array logic.
 *
 * Originally, the maximum number of available buffer descriptors
 * was hardwired into the model of the Ethernet MAC. Two conditional
 * checks had to be rewritten to make sure that the _ETHOC_DESC_SIZE_
 * constant is checked instead.
 *
 * \pre: size must be an even number greater than or equal to 2
 */
#define _ETHOC_DESC_SIZE_ 8

/**
 * Hardware model of OpenCores Ethernet MAC with MII to PHY
 */
typedef struct OpenEthState {
    struct NICState *nic;
    hw_irq irq;

    Mii mii;
    uint32_t regs[REG_MAX];
    unsigned tx_desc;
    unsigned rx_desc;
    open_eth_desc desc[_ETHOC_DESC_SIZE_];

#ifndef _CBMC_
    /*
     * non-reentrant
     */
    pthread_mutex_t lock;
#endif

    /* object of low-level software which controls the MAC */
    void *fw;
} OpenEthState;

/**
 * open_eth_reg_read:
 * @s: self object pointer
 * @addr: address of register
 *
 * Atomically reads and returns the content of a register.
 *
 * @see_also: Chapter 3 in data sheet
 * @see_also: open_eth_reg()
 * @warning: non-reentrant
 */
uint32_t open_eth_reg_read(OpenEthState *s, hwaddr addr);

/**
 * open_eth_reg_write:
 * @s: self object pointer
 * @addr: address of register
 * @val: double word to be written
 *
 * Atomically overwrites the content of a register with the given value.
 *
 * Note that certain register values (e.g. @TX_BD_NUM) should only be changed
 * when the @MODER_TXEN and @MODER_RXEN bits are both disabled. The new value
 * could also be subject to range restrictions. For example, @TX_BD_NUM should
 * never be greater than 0x80h.
 *
 * @see_also: Chapter 3 in data sheet
 * @see_also: open_eth_reg()
 * @warning: non-reentrant
 */
void open_eth_reg_write(OpenEthState *s, hwaddr addr, uint32_t val);

/**
 * open_eth_desc_read:
 * @s: self object pointer
 * @addr: address of descriptor starting at zero
 *
 * Atomically reads and returns a single buffer descriptor out of a maximum
 * of 128 possible ones. The register indexed by @TX_BD_NUM determines the
 * address boundary between transmission and reception buffer descriptors.
 * This means that every TX BD address must be strictly less than @TX_BD_NUM
 * whereas every RX BD address must be greater or equal to @TX_BD_NUM.
 *
 * @see_also: Section 4.2.2 in data sheet
 * @warning: non-reentrant
 */
uint64_t open_eth_desc_read(OpenEthState *s, hwaddr addr);

/**
 * open_eth_desc_write:
 * @s: self object pointer
 * @addr: address of descriptor starting at zero
 * @val: double word to be written
 *
 * Atomically overwrites a buffer descriptor. Each descriptor is 64 bits
 * wide. There are at most 128 such descriptors. The register indexed by
 * @TX_BD_NUM should hold the actual number of used descriptors. The lower
 * 32 bits hold the buffer descriptor's status whereas the upper 32 bits
 * hold a DMA address.
 *
 * @see_also: Section 4.2.2 in data sheet
 * @warning: non-reentrant
 */
void open_eth_desc_write(OpenEthState *s, hwaddr addr, uint64_t val);

/**
 * open_eth_can_receive:
 * @s: self object pointer
 *
 * Atomically checks whether open_eth_receive(@s) can be called.
 *
 * @warning: non-reentrant
 */
int open_eth_can_receive(OpenEthState *s);

/**
 * open_eth_receive:
 * @s: self object pointer
 * @buf: bytes to be written
 * @size: maximum number of bytes to be written
 *
 * Atomically writes at most @size bytes in the read-only @buf array to memory
 * according to the direct-memory address (DMA) in the current buffer descriptor.
 *
 * @warning: non-reentrant
 */
size_t open_eth_receive(OpenEthState *s, const uint8_t *buf, size_t size);

/**
 * open_eth_set_link_status:
 * @s: self object pointer
 * @link_down: flag to be written
 *
 * Atomically update net client's link status.
 *
 * @warning: non-reentrant
 */
void open_eth_set_link_status(OpenEthState *s, bool link_down);


/**
 * internal_open_eth_set_link_status:
 * @s: self object pointer
 * @link_down: flag to be written
 *
 * Update net client's link status. Call this function only when the
 * lock on the hardware model has been already aquired!
 */
void internal_open_eth_set_link_status(OpenEthState *s, bool link_down);

#endif
