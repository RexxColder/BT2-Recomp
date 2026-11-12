#include "common.h"

extern void *memcpy(void *dst, const void *src, u32 n);

/* 0x002CC500: copies an L-byte block into a ring of N bytes (arg5 = N, arg7 = L) starting at
 * offset arg1 (arg3 is the offset allowance). Returns 0 when arg1 + arg3 is below N + L, else N + L.
 * The block is split at the ring end: the part that fits goes to arg0 + ..., the rest wraps to
 * arg2, or arg2 + ... for the second source (arg6). Each case is a sequence of memcpy calls. */
s32 func_002CC500(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, u8 *arg4, s32 arg5, u8 *arg6, s32 arg7) {
    s32 n = arg5;
    s32 l = arg7;
    s32 fp = n + l;
    s32 s3;

    if (arg1 + arg3 < fp) {
        return 0;
    }

    if (n >= arg1) {
        memcpy(arg0, arg4, arg1);
        memcpy(arg2, arg4 + arg1, n - arg1);
        memcpy(arg2 + n - arg1, arg6, l);
        return fp;
    }

    s3 = arg1 - n;
    if (l < s3) {
        memcpy(arg0, arg4, n);
        memcpy(arg0 + n, arg6, l);
        return fp;
    }

    memcpy(arg0, arg4, n);
    memcpy(arg0 + n, arg6, s3);
    memcpy(arg2, arg6 + arg1 - n, l - s3);
    return fp;
}
