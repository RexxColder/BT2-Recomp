#include "common.h"

s32 func_002C0178(s32 arg0, s32 arg1, s32 arg2);
u32 func_002C67D0(s32 arg0, s32 arg1, s32 arg2);
void func_002C9BB0(s32 arg0, s32 arg1);

s32 func_002C9A50(s32 arg0, s32 arg2) {
    s32 sp[8];
    s32 sp20[8];
    s32 v0;
    s32 s0;
    s32 a0v;
    s32 a2v;
    s32 minv;
    s32 ptr;
    u32 temp;

    v0 = func_002C0178(arg0, *(s32 *)(arg0 + 0x1FC8), (s32)sp);
    if (v0 != 0) {
        return 0;
    }
    if (sp[1] == 0) {
        return 0;
    }
    temp = func_002C67D0((s32)sp, arg2, (s32)sp20);
    if (temp == 0) {
        s0 = (sp[1] + sp[3]) - 3;
        if (s0 < 0) {
            s0 = 0;
        }
    } else {
        if (temp >= (u32)sp[0] && temp < (u32)(sp[0] + sp[1])) {
            s0 = (s32)(temp - (u32)sp[0]);
        } else {
            s0 = 0;
            if (temp >= (u32)sp[2] && temp < (u32)(sp[2] + sp[3])) {
                s0 = (s32)(temp - (u32)sp[2]) + sp[1];
            }
        }
    }
    func_002C9BB0(arg0, s0);

    a2v = 0;
    a0v = 0;
    minv = (s0 < 4) ? s0 : 3;
    while (a0v < minv) {
        if (a0v < sp[1]) {
            ptr = sp[0] + a0v;
        } else {
            ptr = sp[2] + (a0v - sp[1]);
        }
        a0v += 1;
        if (*(s8 *)ptr != 0) {
            a2v = 1;
            break;
        }
    }
    if (a2v != 0) {
        *(s64 *)(arg0 + 0x9B0) = *(s64 *)(arg0 + 0x9B0) + s0;
    }
    *(s64 *)(arg0 + 0x9A8) = *(s64 *)(arg0 + 0x9A8) + s0;
    return s0;
}
