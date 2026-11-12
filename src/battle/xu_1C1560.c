#include "common.h"
s32 func_001C14A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_001C1560(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    s32 r;
    r = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 0);
    if (r != 0) {
        *(f32 *)(r + 0xC) = farg0;
    }
}
