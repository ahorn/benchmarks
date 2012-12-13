#ifndef NET_H
#define NET_H

#include <unistd.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct NetClientInfo NetClientInfo;
typedef struct NetClientState NetClientState;
typedef struct NICState NICState;

typedef int (NetCanReceive)(NetClientState *);
typedef ssize_t (NetReceive)(NetClientState *, const uint8_t *, size_t);
typedef void (LinkStatusChanged)(NetClientState *);

struct NetClientInfo {
    NetCanReceive *can_receive;
    NetReceive *receive;
    LinkStatusChanged *link_status_changed;
    /* ... */
};

struct NetClientState {
    NetClientInfo *info;
    int link_down;
    NetClientState *peer;
    unsigned receive_disabled : 1;
    /* ... */
};

struct NICState {
    NetClientState nc;
    void *opaque;
    /* ... */
};

bool can_send_packet(NetClientState *sender);
ssize_t send_packet(NetClientState *sender, const uint8_t *buf, size_t size);

#define POLYNOMIAL 0x04c11db6
unsigned compute_mcast_idx(const uint8_t *ep);

#endif
