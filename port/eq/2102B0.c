#include "common.h"

void func_0020FAD0(s32 arg0, void *arg1, void *arg2, s32 arg3, f32 farg0, f32 farg1);
s32 BtlChar_FrameMod(s32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 *D_003876A0;

void func_002102B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1) {
    s32 sp[2];
    u8 *s2;
    u8 s0;
    s32 s1;
    s32 ret;

    s2 = *(u8 **)(D_003876A0 + 0xB4) + arg1 * 6;
    func_0020FAD0(arg0, sp, &sp[1], arg3, farg0, farg1);
    s0 = *(u8 *)(s2 + 4);
    s1 = *(s16 *)(s2 + 2) - *(s16 *)(s2 + 0);
    if (s0 == 0) {
        s0 = 1;
    }
    ret = BtlChar_FrameMod(s0);
    s1 = s1 * ret;
    s1 = s1 / (s32)(s0 - 1);
    func_00297FE0(2, arg1, sp[0], sp[1], *(s16 *)(s2 + 0) + s1);
}
