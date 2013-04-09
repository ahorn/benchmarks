/*
 * We implement spinlocks symbolically
 */
#ifndef LOCK_H
#define LOCK_H

struct spinlock_t {};
typedef struct spinlock_t spinlock_t;

static inline void spin_lock_irq(spinlock_t *lock) {}
static inline void spin_unlock_irq(spinlock_t *lock) {}

#endif
