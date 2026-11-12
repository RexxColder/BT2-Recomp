#include "common.h"

s32 memcmp(void *a, void *b, u32 n);
extern u8 D_0037BC60[] __attribute__((section(".data")));

s32 func_002ECE88(s32 arg0) {
    s32 ret;
    u8 *p;
    u32 v;

    ret = -4;
    p = (u8 *)arg0;
    if (memcmp((void *)arg0, D_0037BC60, 3) == 0) {
        v = p[4] | ((u32)p[7] << 24) | ((u32)p[6] << 16) | ((u32)p[5] << 8);
        ret = (s32)v;
    }
    return ret;
}
