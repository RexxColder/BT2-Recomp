#include "common.h"

extern u8 D_00348DEF __attribute__((section(".data")));

s32 func_002EAA30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

s32 func_002EA788(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_002EAA30(arg0, arg1, arg2, arg3, (s32) ((u32) &D_00348DEF & 0xFFFFFFC0), 0x800);
}
