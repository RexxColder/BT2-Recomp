#include "common.h"

s32 func_0019E4E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0);
s32 func_0019ECF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0);
extern u8 *D_003877F8;

void func_0019F4A0(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg1 * 0x3F;
    func_0019E4E0(*(s32 *)(D_003877F8 + 0x1DC), (s32)(D_003877F8 + temp_s0 + 0x28), arg1, arg0, 0, 1.0f);
    func_0019E4E0(*(s32 *)(D_003877F8 + 0x1E0), (s32)(D_003877F8 + temp_s0 + 0x31), arg1, arg0, 0, 1.0f);
    func_0019ECF0(*(s32 *)(D_003877F8 + 0x1E4), (s32)(D_003877F8 + 0x3A), arg0, 0, *(s32 *)D_003877F8, 1.0f);
}
