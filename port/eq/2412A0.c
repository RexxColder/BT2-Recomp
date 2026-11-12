#include "common.h"

s32 func_001F99B0(void *arg0, s32 arg1);
s32 func_001F99E8(void *arg0, s32 arg1);
s32 func_00240FF0(void *arg0, s32 arg1);
s32 func_00241020(void *arg0, s32 arg1);
s32 func_002411A0(void *arg0, s32 arg1);

s32 func_002412A0(void *arg0, s32 arg1, s32 arg2) {
    s32 s0;
    s32 v;
    s32 idx;
    u8 *tbl;
    u8 *ptr;

    idx = func_002411A0(arg0, arg1);
    tbl = *(u8 **)((u8 *)arg0 + 0x1530);
    ptr = *(u8 **)(tbl + 0x980);
    s0 = *(s32 *)(ptr + idx * 4 + 0xC);
    if (arg1 >= 2 && arg1 <= 4) {
        if (arg1 == 4) {
            v = func_001F99E8(arg0, 0);
        } else {
            v = func_001F99B0(arg0, 0);
        }
        s0 = (s0 * v) / 100;
    }
    if ((arg2 & 0xFF) == 0) {
        v = func_00240FF0(arg0, arg1);
        if (v >= 2) {
            s0 = s0 / v;
        }
        v = func_00241020(arg0, arg1);
        if (v >= 2) {
            s0 = s0 / v;
        }
    }
    return s0;
}
