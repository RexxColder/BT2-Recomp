#include "common.h"

f32 func_00273000(s32 arg0);
void func_0027F7B0(s32 arg0, s32 arg1, f32 farg0);
extern u8 *gBtlCam;

void func_0027FA28(u8 *arg0, s32 arg1, s32 arg2) {
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f12;

    f0 = func_00273000((s32)arg0);
    f0 = -f0;
    f1 = *(f32 *)(gBtlCam + arg2 * 0x300 + 0x274);
    f1 = -f1;
    f2 = (f32)*(u8 *)(arg0 + 0x61F);
    f2 = f2 / 255.0f;
    f1 = f1 / f0;
    f1 = f1 * 0.5f;
    f12 = 1.0f - f1;
    f12 = f2 * f12;
    func_0027F7B0(*(s32 *)(arg0 + 0xB90), (s32)(arg0 + 0x620), f12);
}
