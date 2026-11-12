#include "common.h"

s32 func_002D45E8(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

/* 0x002D48D0(obj, dst): src = (*(obj + 4)) + 0x40 (read before the call). When func_002D45E8(obj) != 0: memset(dst,
 * 0, 13), copy the first 12 bytes of src to dst and return 1; otherwise return 0. */
s32 func_002D48D0(u8 *arg0, u8 *arg1) {
    u8 *src = (u8 *)*(s32 *)(arg0 + 4) + 0x40;
    s32 k;

    if (func_002D45E8((s32)arg0) == 0) {
        return 0;
    }
    memset(arg1, 0, 13);
    for (k = 0; k < 12; k++) {
        arg1[k] = src[k];
    }
    return 1;
}
