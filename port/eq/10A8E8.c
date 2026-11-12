#include "common.h"

s32 Ramp_Step(s32 arg0);
/* GUESS arity: the asm sets a1 (the D_003876A0 pointer) and a2 (0x400) before the call */
f32 Ramp_Start(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2);
void func_0010B0C8(void);
extern u8 *D_003876A0;

s32 func_0010A8E8(s32 arg0) {
    u8 *base;
    s32 state;

    base = (u8 *)arg0;
    state = base[8];
    switch (state) {
    case 0:
        if (Ramp_Step(arg0 + 0xC) != 0) {
            func_0010B0C8();
            *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & (s64)-0x201;
            *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x400;
            Ramp_Start(arg0 + 0xC, (s32)D_003876A0, 0x400, 2.0f, 0.0f, 1.0f);
            base[8] = base[8] + 1;
        }
        return 2;
    case 1:
        if (Ramp_Step(arg0 + 0xC) != 0) {
            return 3;
        }
        return 2;
    default:
        return 2;
    }
}
