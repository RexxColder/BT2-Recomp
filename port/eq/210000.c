#include "common.h"

void func_0020FAD0(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
s32 BtlChar_FrameMod(s32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 *D_003876A0;
extern f32 D_003859FC;

void func_00210000(s32 arg0, s32 arg1) {
    s32 sp[2];
    u8 *s2;
    s32 s0;
    s32 h0;
    s32 s1;
    s32 fm;
    s32 t0;

    s2 = *(u8 **)(D_003876A0 + 0xB0) + (arg1 * 6);
    func_0020FAD0(arg0, (s32)sp, (s32)&sp[1], 200.0f, D_003859FC);
    s0 = *(u8 *)(s2 + 4);
    if (s0 == 0) {
        s0 = 1;
    }
    h0 = *(s16 *)(s2 + 0);
    s1 = *(s16 *)(s2 + 2) - h0;
    fm = BtlChar_FrameMod(s0);
    s1 = s1 * fm;
    t0 = *(s16 *)(s2 + 0);
    s0 = s0 - 1;
    t0 = t0 + (s1 / s0);
    func_00297FE0(1, arg1, sp[0], sp[1], t0);
}
