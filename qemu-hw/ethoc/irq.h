/* Generic IRQ/GPIO pin infrastructure. 
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later. See the COPYING file in the top-level directory.
 */
#ifndef QEMU_IRQ_H
#define QEMU_IRQ_H

typedef void (*qemu_irq_handler)(void *opaque, int n, int level);

typedef struct IRQState *qemu_irq;

typedef struct IRQState {
    qemu_irq_handler handler;
    void *opaque;
    int n;
} IRQState;

void qemu_set_irq(qemu_irq irq, int level);

/* ... */

#endif
