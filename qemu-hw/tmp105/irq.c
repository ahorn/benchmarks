/*
 * QEMU IRQ/GPIO common code.
 *
 * Copyright (c) 2007 CodeSourcery.
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later. See the COPYING file in the top-level directory.
 */

#include "irq.h"

void qemu_set_irq(qemu_irq irq, int level)
{
    if (!irq)
        return;

    irq->handler(irq->opaque, irq->n, level);
}

/* ... */
