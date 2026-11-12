#include "common.h"

s32 func_002C3210(u8 *arg0);
void func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002D07B0(u8 *arg0, s32 arg1);

void func_002BF2F0(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *vt;

    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF0001A1);
        return;
    }
    if (func_002D07B0(arg0, 6) != 0) {
        vt = *(u8 **)(arg0 + 0x2114);
        ((void (*)(u8 *, s32, s32)) *(s32 *)(vt + 0x4))(arg0, arg1, arg2);
    }
}
