#include "common.h"

s32 func_002D5210(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

/* 0x002D5120(obj, idx, dst): dst[0] = 0; src = func_002D5210(obj, idx & 0xFF). When src == NULL return 0; otherwise
 * memset(dst, 0, 13), copy 12 bytes from src to dst and return 1. */
s32 func_002D5120(s32 arg0, s32 arg1, u8 *arg2) {
    u8 *src;
    s32 k;

    arg2[0] = 0;
    src = (u8 *)func_002D5210(arg0, arg1 & 0xFF);
    if (src == 0) {
        return 0;
    }
    memset(arg2, 0, 13);
    for (k = 0; k < 12; k++) {
        arg2[k] = src[k];
    }
    return 1;
}
