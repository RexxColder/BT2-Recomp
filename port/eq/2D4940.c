#include "common.h"

s32 func_002D45E8(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

/* 0x002D4940(obj, dst): dst[0] = 0; src = *(obj + 4) (read before the call). When func_002D45E8(obj) != 0: memset(dst,
 * 0, 13), copy 12 bytes from src + 0x4C to dst and return 1; otherwise return 0. */
s32 func_002D4940(u8 *arg0, u8 *arg1) {
    u8 *src = (u8 *)*(s32 *)(arg0 + 4);
    s32 k;

    arg1[0] = 0;
    if (func_002D45E8((s32)arg0) == 0) {
        return 0;
    }
    memset(arg1, 0, 13);
    for (k = 0; k < 12; k++) {
        arg1[k] = src[0x4C + k];
    }
    return 1;
}
