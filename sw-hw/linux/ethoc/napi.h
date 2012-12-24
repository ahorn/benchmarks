/*
 * Simplified NAPI implementation whose concurrency semantics is
 * given through a symbolic encoding of partial orders.
 */
#ifndef NAPI_H
#define NAPI_H

/*
 * Structure for NAPI scheduling similar to tasklet but with weighting
 */
struct napi_struct {
	/* thread local variable */
	int	complete;

	/* constant after initialization */
	int	weight;

	/* used for synchronization (e.g. see poll()) */
	int	sched;

	/* relies on happens-before order on sched field */
	int	is_disabling;

	/* poll() will not be invoked simultaneously.
 	 * Of course, this does not mean that poll() cannot be preempted.
 	 */
	int	(*poll)(struct napi_struct *, int);

};

/**
 * In our analysis, this is an atomic test and set of the given flag.
 * It is assumed that this function also serves as a memory barrier.
 */
static inline int test_and_set(int *flag)
{
	int _flag = *flag;
	*flag = 1;
	return _flag;
}

/**
 * In our analysis, this is an atomic test and clear of the given flag.
 * It is assumed that this function also serves as a memory barrier.
 */
static inline int test_and_clear(int *flag)
{
	int _flag = *flag;
	*flag = 0;
	return _flag;
}

/**
 * napi_pool_loop - simplified NAPI implementation
 *
 * In our analysis, this function executes as a light-weight thread.
 * Hardware interrupts must be disabled during its execution. The NAPI
 * implementation guarantees that poll() calls cannot run concurrently
 * (see also netpoll_poll_lock() in actual implementation).
 *
 * Background: net_rx_action() in linux/net/core/dev.c implements a round-robin
 * schedule with a deque data structure. Since we do not intend to model
 * this in our experiments, we abstract it through a loop which repeats until
 * the driver has not exhausted its budget, i.e. the driver has processed
 * all incoming packets within poll() and called napi_complete().
 */
static inline void napi_poll_loop(struct napi_struct *n)
{
	int work;

	n->complete = 0;
	while (!n->complete) {
		n->poll(n, n->weight);
	}
}

/**
 * napi_schedule - schedule NAPI poll
 * @n: napi context
 *
 * Schedule NAPI poll routine to be called if it is not already
 * running. The poll() call happens some time in the future.
 */
static inline void napi_schedule(struct napi_struct *n)
{
	if (!test_and_set(&n->sched) && !n->is_disabling) {
		/* asynchronous call */
		napi_poll_loop(n);
	}
}

/* ... */

/**
 * napi_enable - enable NAPI scheduling
 * @n: napi context
 *
 * Resume NAPI from being scheduled on this context.
 * Must be paired with napi_disable.
 */
static inline void napi_enable(struct napi_struct *n)
{
	assert(test_and_clear(&n->sched));
}

/**
 * napi_disable - prevent NAPI from scheduling
 * @n: napi context
 *
 * Stop NAPI from being scheduled on this context.
 * Waits till any outstanding processing completes.
 */
static inline void napi_disable(struct napi_struct *n)
{
	n->is_disabling = true;
	while (test_and_set(&n->sched)) {
	}
	n->is_disabling = false;
}

/**
 * napi_complete - mark NAPI as done before switching back to interrupt mode
 * @n: napi context
 *
 * If a driver consumes less than the assigned budget in its run of the
 * poll handler, it must end the polling mode by calling this function.
 */
static inline void napi_complete(struct napi_struct *n)
{
	/* happens-before order through napi_schedule() */
	assert(n->sched);
	n->complete = 1;
	test_and_clear(&n->sched);
}

#endif
