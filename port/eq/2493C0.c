#include "common.h"

void func_001017F0(s32 arg0, s32 arg1);
void func_00247E80(s32 arg0);
extern u8 *D_00387F2C;

/* 0x002493C0: func_001017F0(arg2 or arg1, 0) + arg4 by the flag bit 0 of D_00387F2C+0x1008; if arg0 != 0 take
 * the word at arg0 + 4*(2*arg4 + arg3) (+8 when the flag is set), clear its low 2 bits and tail-call
 * func_00247E80(arg0 + that). */
void func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 flag;
    s32 v;

    flag = *(s32 *)(D_00387F2C + 0x1008) & 1;
    if (flag) {
        func_001017F0(arg2 + arg4, 0);
    } else {
        func_001017F0(arg1 + arg4, 0);
    }
    if (arg0 == 0) {
        return;
    }
    if (flag) {
        v = *(s32 *)((u8 *)arg0 + (2 * arg4 + arg3) * 4 + 8);
    } else {
        v = *(s32 *)((u8 *)arg0 + (2 * arg4 + arg3) * 4 + 4);
    }
    func_00247E80(arg0 + (((u32)v >> 2) << 2));
}
