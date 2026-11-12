#include "common.h"

s32 func_002C2000(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_0037A0C0[] __attribute__((section(".data")));

s32 func_002C1E28(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    u8 *b = (u8 *)sp;
    s32 idx;
    s32 temp;

    if (func_002C2000(sp, arg0, arg1, arg3) == 0) {
        return -1;
    }
    idx = (b[0] << 4) + b[2];
    temp = D_0037A0C0[idx];
    if (temp != -1) {
        return temp * 0x3E8;
    }
    return -1;
}
