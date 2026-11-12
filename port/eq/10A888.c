#include "common.h"

f32 Ramp_Start(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2);
void func_0010B5D0(void);
extern f32 D_00383E1C;
extern s32 D_003876A0;

s32 func_0010A888(s32 arg0) {
    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x200;
    *(s8 *)(arg0 + 8) = 0;
    Ramp_Start(arg0 + 0xC, D_003876A0, 0x200, D_00383E1C, 0.0f, 1.0f);
    func_0010B5D0();
    return 1;
}
