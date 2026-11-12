#include "common.h"

/* GUESS arity: the asm sets a0..a3 before the tail jump; ctx.h says 2 */
s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002C0750(u8 *arg0, s32 arg1, s32 *arg2) {
    u8 *temp;

    *arg2 = 0;
    temp = arg0 + 0x1310 + arg1 * 0x74;
    if (*(s32 *)(temp + 4) == 0) {
        return func_002C2FF0((s32)arg0, 0xFF000401, (s32)arg2, (s32)temp);
    }
    *arg2 = *(s32 *)(temp + 0x14);
    return 0;
}
