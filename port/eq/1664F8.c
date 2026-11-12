#include "common.h"

s32 func_00129C28(s32 arg0, s32 arg1);
void func_001917B0(s32 arg0, s32 arg1, s32 arg2);
f32 sinf(f32 x);
extern f32 D_003847CC;
extern f32 D_003847D0;
extern f32 D_003847D4;

void func_001664F8(s32 arg0) {
    s32 sp[4];
    f32 *spf;
    f32 temp_f1;
    f32 temp_f3;

    spf = (f32 *) sp;
    func_00129C28((s32) sp, arg0 + 0x10);
    temp_f3 = *(f32 *) (arg0 + 0x30) + D_003847CC;
    temp_f1 = spf[1] + (sinf(*(f32 *) (arg0 + 0x30)) * 10.0f);
    *(f32 *) (arg0 + 0x30) = temp_f3;
    if (D_003847D0 <= temp_f3) {
        *(f32 *) (arg0 + 0x30) = temp_f3 - D_003847D4;
    }
    spf[1] = temp_f1;
    func_001917B0(*(s32 *) (arg0 + 4), 1, (s32) sp);
}
