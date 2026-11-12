#include "common.h"

void func_002653E8(s32 arg0, s32 arg1);
extern s32 D_00387A40;

void func_002658A8(s32 arg0) {
    s32 s0 = 0;
    s32 s1 = 0;
    s32 a0;

    if (*(s32 *)(D_00387A40 + 4) <= 0) {
        return;
    }
    do {
        a0 = *(s32 *)D_00387A40 + s0;
        s0 += 0x18580;
        s1 += 1;
        func_002653E8(a0, arg0);
    } while (s1 < *(s32 *)(D_00387A40 + 4));
}
