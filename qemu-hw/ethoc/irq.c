/*
 * QEMU IRQ/GPIO common code.
 *
 * Copyright (c) 2007 CodeSourcery.
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later. See the COPYING file in the top-level directory.
 */

#include "irq.h"

void do_handler(hw_irq irq, int level)
{
  int n=irq->n;
__CPROVER_ASYNC_1:
    irq->handler(irq->opaque, n, level);
}

void hw_set_irq(hw_irq irq, int level)
{
    if (!irq)
        return;

    do_handler(irq, level);
}

/* ... */
