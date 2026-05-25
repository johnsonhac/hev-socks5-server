/*
 ============================================================================
 Name        : hev-drop.h
 Description : Global drop-mode flag.
               When enabled, the worker closes newly accepted connections
               immediately so no traffic can leak outside the VPN tunnel
               while the tunnel is restarting.
               Existing sessions keep their file-descriptors open; the TCP
               state on the client side is therefore preserved (the client
               sees a stall, not a reset) for the few seconds the VPN is
               coming back up.
 ============================================================================
 */

#ifndef __HEV_DROP_H__
#define __HEV_DROP_H__

#include <stdatomic.h>

/* Defined once in hev-jni.c, used in hev-socks5-worker.c */
extern atomic_int hev_drop_mode;

static inline int
hev_drop_mode_get (void)
{
    return atomic_load_explicit (&hev_drop_mode, memory_order_acquire);
}

static inline void
hev_drop_mode_set (int enable)
{
    atomic_store_explicit (&hev_drop_mode, enable, memory_order_release);
}

#endif /* __HEV_DROP_H__ */
