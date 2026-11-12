#include "common.h"

s32 func_001267E8(s32 arg0, s32 arg1);
void func_001857A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
void func_00185368(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0, f32 farg1);
void func_00185A18(s32 arg0, s32 arg1, s32 arg2);

void func_001846E0(s32 arg0) {
    s32 s1;
    s32 s0;
    s32 a2;

    s1 = *(s32 *)(arg0 + 0x38);
    s0 = *(s32 *)(s1 + 0x30);
    if (func_001267E8(*(s32 *)(s1 + 0x94), *(u8 *)(s1 + 0x1A0)) != 0) {
        return;
    }
    a2 = *(s32 *)(s0 + 0xA4);
    if (a2 & 2) {
        if (a2 & 0x18) {
            func_001857A0(s1, ((a2 >> 10) ^ 1) & 1, (a2 >> 3) & 1, (a2 >> 9) & 1,
                          *(f32 *)(s0 + 0x34), *(f32 *)(s0 + 0x38));
        } else {
            func_00185368(s1, ((a2 >> 10) ^ 1) & 1, 0, 1, (a2 >> 9) & 1,
                          *(f32 *)(s0 + 0x34), *(f32 *)(s0 + 0x38));
        }
        a2 = *(s32 *)(s0 + 0xA4);
    }
    if (a2 & 1) {
        if (a2 & 0x20) {
            func_00185A18(s1, ((a2 >> 10) ^ 1) & 1, (a2 >> 9) & 1);
            return;
        }
        func_00185368(s1, ((a2 >> 10) ^ 1) & 1, 1, 0, (a2 >> 9) & 1,
                      *(f32 *)(s0 + 0x34), *(f32 *)(s0 + 0x38));
    }
}
