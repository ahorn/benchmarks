#ifndef _NET_H_
#define _NET_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct NetClientInfo NetClientInfo;
typedef struct NetClientState NetClientState;
typedef struct NICState NICState;

typedef void (LinkStatusChanged)(NetClientState *);

struct NetClientInfo {
    /*
     * Lock on hardware model has been already acquired when the LinkStatusChanged
     * callback function is being invoked. Since this lock is non-reentrant (see
     * "ethow-hw.h"), LinkStatusChanged must not attempt to acquire the lock.
     */
    LinkStatusChanged *link_status_changed;

    /* ... */
};

struct NetClientState {
    NetClientInfo *info;
    int link_down;
    unsigned receive_disabled : 1;

    /* ... */
};

struct NICState {
    NetClientState nc;
    void *opaque;

    /* ... */
};

#define POLYNOMIAL 0x04c11db6
unsigned compute_mcast_idx(const uint8_t *ep);

#endif
