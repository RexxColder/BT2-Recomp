#include "common.h"

s32 sceSifCallRpc(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
extern u8 D_00355C70[] __attribute__((section(".data")));
extern s32 D_0039DC80[] __attribute__((section(".data")));
extern s32 D_0039DD80 __attribute__((section(".data")));

s32 func_002FCAC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_0039DC80[0] = arg0;
    D_0039DC80[1] = arg1;
    D_0039DC80[2] = arg2;
    D_0039DC80[3] = arg3;
    sceSifCallRpc((s32)D_00355C70, 2, 0, (s32)D_0039DC80, 0x10, (s32)&D_0039DD80, 4, 0, 0);
    return D_0039DD80;
}
