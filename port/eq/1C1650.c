#include "common.h"

s32 func_001C14A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_001C1650(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1) {
    s32 temp_v0 = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 3);

    if (temp_v0 != 0) {
        *(f32 *)(temp_v0 + 0xC) = farg0;
        *(f32 *)(temp_v0 + 0x10) = farg1;
    }
}
