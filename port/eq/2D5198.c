#include "common.h"

s32 func_002D5210(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

/* 0x002D5198(obj, idx, dst): as 0x002D5120 (func_002D5210(obj, idx & 0xFF) gives src), but the 12 bytes are
 * copied from src + 0xC. */
s32 func_002D5198(s32 arg0, s32 arg1, u8 *arg2) {
    u8 *src;
    s32 k;

    arg2[0] = 0;
    src = (u8 *)func_002D5210(arg0, arg1 & 0xFF);
    if (src == 0) {
        return 0;
    }
    memset(arg2, 0, 13);
    for (k = 0; k < 12; k++) {
        arg2[k] = src[0xC + k];
    }
    return 1;
}
