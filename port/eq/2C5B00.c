#include "common.h"

/* GUESS arity: the tail call passes a0 (arg0), a2 and a3 through with a1 = 0xFF000F1D */
s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002CA118(s32 arg0);

s32 func_002C5B00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *base;
    u8 *t0;
    s32 a0i;
    s32 a1v;
    s32 a2v;
    s32 lim;
    s32 off;

    base = (u8 *)arg0;
    t0 = (u8 *)(*(s32 *)(base + 0x1FC0) + 0x1080);
    if (arg1 == 0 || arg2 == 0 || arg3 == 0) {
        func_002CA118((s32)t0);
        return 0;
    }
    if (arg2 < *(s32 *)(base + 0x2C) + 4) {
        return func_002C2FF0(arg0, 0xFF000F1D, arg2, arg3);
    }
    *(s32 *)t0 = arg1;
    a0i = 0;
    *(s32 *)(t0 + 0xC) = arg1;
    a1v = arg1 + arg3;
    *(s32 *)(t0 + 4) = arg2;
    a2v = arg2 - 2;
    *(s32 *)(t0 + 0x14) = a1v;
    a1v = a1v + arg3;
    *(s32 *)(t0 + 8) = arg3;
    *(s32 *)(t0 + 0x10) = 0;
    *(s32 *)(t0 + 0x18) = 0;
    lim = (a2v < 0x11) ? a2v : 0x10;
    while (a0i < lim) {
        off = a0i * 8 + 0x10;
        a0i += 1;
        *(s32 *)(t0 + off + 0x10) = 0;
        *(s32 *)(t0 + off + 0xC) = a1v;
        a1v += arg3;
    }
    return 0;
}
