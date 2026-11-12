#include "common.h"

s32 func_001C14A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_001C1720(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 v3 = farg3;
    f32 v0 = farg0;
    f32 v1 = farg1;
    f32 v2 = farg2;
    s32 r;

    r = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 5);
    if (r != 0) {
        *(f32 *)(r + 0xC) = v0;
        *(f32 *)(r + 0x10) = v1;
        *(f32 *)(r + 0x14) = v2;
        *(f32 *)(r + 0x18) = v3;
    }
}
