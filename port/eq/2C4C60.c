#include "common.h"

/* GUESS arity: the asm sets a0..a3 before the jal; ctx.h says 2 */
s32 func_002C06B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
u8 *func_002C3D18(s32 arg0);

s32 func_002C4C60(s32 arg0) {
    u8 *t;
    u8 *p;
    s32 a2;
    s32 a3;
    s32 lim;
    s32 ret;

    t = func_002C3D18(arg0);
    p = (u8 *)arg0 + 0xA0C;
    a2 = *(s32 *)((u8 *)arg0 + 0x8);
    a3 = *(s32 *)(p + 0x58);
    if (a2 <= 0) {
        a2 = *(s32 *)(t + 0xC);
    }
    if (a2 <= 0) {
        a2 = a3;
    }
    lim = (a2 < a3) ? a2 : a3;
    ret = func_002C06B0(arg0, 0, a2, a3);
    return ret < lim ? 0 : 1;
}
