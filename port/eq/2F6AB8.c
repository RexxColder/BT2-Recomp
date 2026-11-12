#include "common.h"

/* GUESS arity: a0/a1 are the function's own parameters, passed through; 10 args from the asm */
s32 func_002E9688(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9);

s32 func_002F6AB8(u16 *arg0, s32 arg1, s32 *arg2) {
    u8 buf[0x14];
    s32 var_v0;
    u16 temp_v1;

    var_v0 = 0;
    if (arg1 >= 2) {
        temp_v1 = arg0[0];
        if ((((temp_v1 >> 8) | (temp_v1 << 8)) & 0xFFFF) == 0x8000) {
            if (func_002E9688((s32)arg0, arg1, (s32)(buf + 0x0), (s32)(buf + 0x2), (s32)(buf + 0x3),
                              (s32)(buf + 0x4), (s32)(buf + 0x5), (s32)(buf + 0x10), (s32)(buf + 0x8),
                              (s32)(buf + 0xC)) < 0) {
                return 0;
            }
            var_v0 = 1;
            *arg2 = *(s16 *)(buf + 0x0);
            return var_v0;
        }
    }
    return var_v0;
}
