#include "common.h"

void func_002CB448(s32 arg0);
/* GUESS arity: the asm passes a0 = frame and leaves a1..a3, t0, t1 as they came in. */
s32 func_0032EC60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

/* 0x002CB3D0(obj, a1, a2, a3, t0, t1): a2 = (a2 & 0x0FFFFFFF) | 0x20000000. Stores: obj+0x54 = t1, +0x18 = a3 << 11,
 * +8 = a3, +0 = a1, +0x50 = t0, +4 = a2. A 4-word frame (frame[1] = frame[2] = 1) goes to func_0032EC60 and its
 * result to obj+0x40. Then func_002CB448(obj), the 8 bytes at obj+0x48 = 0, returns 1. */
s32 func_002CB3D0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 frame[4];
    s32 a2;
    s32 ret;

    frame[0] = 0;
    frame[1] = 1;
    frame[2] = 1;
    frame[3] = 0;
    a2 = (arg2 & 0x0FFFFFFF) | 0x20000000;
    *(s32 *)(arg0 + 0x54) = arg5;
    *(s32 *)(arg0 + 0x18) = (s32)((u32)arg3 << 11);
    *(s32 *)(arg0 + 0x8) = arg3;
    *(s32 *)(arg0 + 0x0) = arg1;
    *(s32 *)(arg0 + 0x50) = arg4;
    *(s32 *)(arg0 + 0x4) = a2;
    ret = func_0032EC60((s32)frame, arg1, a2, arg3, arg4, arg5);
    *(s32 *)(arg0 + 0x40) = ret;
    func_002CB448((s32)arg0);
    *(s32 *)(arg0 + 0x48) = 0;
    *(s32 *)(arg0 + 0x4C) = 0;
    return 1;
}
