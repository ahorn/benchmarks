/* Generic IRQ/GPIO pin infrastructure. 
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later. See the COPYING file in the top-level directory.
 */
#ifndef IRQ_H
#define IRQ_H

/**
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

/* ... */

#endif
