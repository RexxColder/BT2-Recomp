#include "common.h"

extern u8 D_00348DEF __attribute__((section(".data")));

s32 func_002EA958(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

/* tail j: a0..a3 pass through, t0/t1 are set here (the f12..f19 and t2/t3 registers are not read down this chain) */
s32 func_002EA5F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_002EA958(arg0, arg1, arg2, arg3, (s32) ((u32) &D_00348DEF & 0xFFFFFFC0), 0x800);
}
