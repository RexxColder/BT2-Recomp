#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
s64 func_0014F0A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_s0;
    s32 temp_t3;

    temp_s0 = (EftShot_TestBits(arg0, 2) == 0) ? 0 : 2;
    temp_s0 = (EftShot_TestBits(arg0, 4) != 0) ? (temp_s0 | 4) : temp_s0;
    temp_s0 = (EftShot_TestBits(arg0, 8) != 0) ? (temp_s0 | 8) : temp_s0;
    temp_s0 = (EftShot_TestBits(arg0, 0x10) != 0) ? (temp_s0 | 0x10) : temp_s0;
    temp_s0 = (EftShot_TestBits(arg0, 0x20) != 0) ? (temp_s0 | 0x20) : temp_s0;
    /* the last flag is left in $t3, the 8th argument of the tail call (j) */
    temp_t3 = (EftShot_TestBits(arg0, 0x40) != 0) ? (temp_s0 | 0x40) : temp_s0;
    return func_0014F0A8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, temp_t3);
}
