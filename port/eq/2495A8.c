#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define ST32(p, off, v) (*(s32 *)((u8 *)(p) + (off)) = (s32)(v))

s32 rand(void);
s32 func_0026EFC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0026EC18(s32 arg0, s32 arg1, s32 arg2);

/* 0x002495A8: step of a state counter (*arg2, codes 0x20..0x30 in a jump table) for the object arg0. Does nothing
 * while *arg1 is negative. Codes 0, 4, 8, 12, 16 call func_0026EFC8 (4 or 8) and func_0026EC18, then count one
 * up. Other codes move on to the wrap-around: the state goes up by one; at 0x88 it may restart at 0 (random
 * choice when the remainder of rand() % 12 is 8 or more) and it is kept below 0x12D. */
void func_002495A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 st;
    s32 idx;
    s32 r;

    if (LD32(arg1, 0) < 0) {
        return;
    }

    st = LD32(arg2, 0);
    idx = st - 0x20;
    if ((u32)idx < 0x11) {
        switch (idx) {
        case 0:
        case 16:
            func_0026EFC8(arg0, arg1, 8, arg3);
            ST32(arg2, 0, LD32(arg2, 0) + 1);
            return;
        case 4:
        case 12:
            func_0026EFC8(arg0, arg1, 4, arg3);
            func_0026EC18(arg0, arg1, arg3);
            ST32(arg2, 0, LD32(arg2, 0) + 1);
            return;
        case 8:
            func_0026EFC8(arg0, arg1, 4, arg3);
            func_0026EC18(arg0, arg1, arg3 + 1);
            ST32(arg2, 0, LD32(arg2, 0) + 1);
            return;
        default:
            break;
        }
    }

    st = st + 1;
    ST32(arg2, 0, st);
    if (!(st < 0x88)) {
        r = rand() % 12;
        if (!(r < 8)) {
            ST32(arg2, 0, 0);
        }
    }
    if (!(LD32(arg2, 0) < 0x12D)) {
        ST32(arg2, 0, 0);
    }
}
