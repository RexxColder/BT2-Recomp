#include "common.h"

u8 *func_00211288(s32 arg0);
s32 func_00200680(u8 *arg0, u8 *arg1);
s32 func_00200890(u8 *arg0, u8 *arg1);
s32 func_00200AD0(u8 *arg0, u8 *arg1);
s32 func_001FD1F0(u8 *arg0);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002029C8(s32 arg0, u8 *arg1) {
    u8 *s1 = func_00211288(arg0);
    s32 s2 = 0;
    u8 *t;
    s32 v1;

    if (*(s32 *)(arg1 + 0xC) != 0) {
        t = *(u8 **)(arg1 + 0x64);
        if (t != NULL) {
            v1 = *(s32 *)(t + 4);
            if (v1 >= 0) {
                if (v1 < 2) {
                    s2 = func_00200890(s1, arg1);
                } else if (v1 < 5) {
                    s2 = func_00200AD0(s1, arg1);
                }
            }
        }
    } else {
        s2 = func_00200680(s1, arg1);
    }
    if (s2 != 0) {
        if (func_001FD1F0(s1) == 8) {
            func_002113C0(s1, 0x10, 0x01000000, 1);
        }
    }
    return s2;
}
