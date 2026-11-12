#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387AE8;
f32 Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);

void func_0027ABE8(f32 farg0) {
    s64 x = *(s64 *)(D_003876A0 + 0x4D8);

    if ((x & 3) != 0) {
        Ramp_Start((s32)(D_00387AE8 + 0x58), farg0, 0.0f, 1.0f);
        *(u8 *)(D_00387AE8 + 0x54) = 1;
    }
}
