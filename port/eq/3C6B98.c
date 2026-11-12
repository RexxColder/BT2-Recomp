#include "common.h"

extern u8 *D_00423114 __attribute__((section(".data")));

s64 GetTimerSystemTime(void);
void func_325370(s64 arg0);
s32 rand(void);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003C6B98: func_325370((s64)(s32)GetTimerSystemTime()). Then by G->0x3638 (G = D_00423114): 0 -> func_2493C0(0, 0x3441 or
 * 0x3442 by rand() & 1, 0x385A, 0, 0); 1 -> func_2493C0(0, 0x3672 or 0x3673, 0x3A8B or 0x3A8C, 0, 0) by rand() & 1;
 * 2 -> func_2493C0(0, 0x3508, 0x3921, 0, 0); anything else does nothing. */
void func_003C6B98(void) {
    u8 *g;
    s32 v;

    func_325370((s64)(s32)GetTimerSystemTime());

    g = D_00423114;
    v = *(s32 *)(g + 0x3638);
    switch (v) {
    case 0:
        if (rand() & 1) {
            func_2493C0(0, 0x3441, 0x385A, 0, 0);
        } else {
            func_2493C0(0, 0x3442, 0x385A, 0, 0);
        }
        return;
    case 1:
        if (rand() & 1) {
            func_2493C0(0, 0x3672, 0x3A8B, 0, 0);
        } else {
            func_2493C0(0, 0x3673, 0x3A8C, 0, 0);
        }
        return;
    case 2:
        func_2493C0(0, 0x3508, 0x3921, 0, 0);
        return;
    default:
        return;
    }
}
