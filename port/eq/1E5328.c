#include "common.h"

s32 func_001E53C0(s32 arg0, s32 arg1, s32 arg2);
s32 func_001E5448(f32 farg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_001E5328(s32 arg0, s32 arg1, s32 arg2) {
    s32 idx;
    s32 mid;

    if (arg1 == arg2) {
        return;
    }
    idx = func_001E53C0(arg0, arg1, arg2);
    if (idx == -1) {
        return;
    }
    mid = func_001E5448(*(f32 *)((u8 *)arg0 + idx * 4), arg0, arg1, arg2, -1);
    func_001E5328(arg0, arg1, mid - 1);
    func_001E5328(arg0, mid, arg2);
}
