#include "common.h"

s32 Rand_Range(s32 arg0, s32 arg1);
extern u8 D_003794C0[] __attribute__((section(".data")));

s32 func_002B9648(u32 arg0) {
    s32 flag;
    s32 v0;
    s32 v1;

    flag = arg0 < 3U;
    v1 = 2;
    if (arg0 != 2) {
        if (flag == 0) {
            v0 = 3;
            v1 = 3;
        } else {
            v0 = 1;
            v1 = 1;
        }
        if (arg0 != (u32)v0) {
            Rand_Range((s32)D_003794C0, flag);
            v1 = 3;
        }
    }
    return v1;
}
