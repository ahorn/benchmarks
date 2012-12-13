#include <errno.h>

#include "net.h"

bool can_send_packet(NetClientState *sender)
{
    NetClientState *peer = sender->peer;

    return peer && !peer->receive_disabled &&
        (!peer->info->can_receive || peer->info->can_receive(peer));
}

ssize_t send_packet(NetClientState *sender, const uint8_t *buf, size_t size)
{
    NetClientState *peer;

    if (can_send_packet(sender)) {
        peer = sender->peer;
        return peer->info->receive(peer, buf, size);
    }

    return -EINVAL;
}

unsigned compute_mcast_idx(const uint8_t *ep)
{
    uint32_t crc;
    int carry, i, j;
    uint8_t b;

    crc = 0xffffffff;
    for (i = 0; i < 6; i++) {
        b = *ep++;
        for (j = 0; j < 8; j++) {
            carry = ((crc & 0x80000000L) ? 1 : 0) ^ (b & 0x01);
            crc <<= 1;
            b >>= 1;
            if (carry) {
                crc = ((crc ^ POLYNOMIAL) | carry);
            }
        }
    }
    return crc >> 26;
}

