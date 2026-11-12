#include "common.h"

/* 0x00206240: if (func_0025FBE8(a0->+0x1530, 1 << 46)) tail func_001FBE80(a0, 3.0f, *(f32 *)D_00385940). */
extern u8 D_00385940[];
s32 func_0025FBE8(s32 arg0, s64 arg1);
s32 func_001FBE80(s32 arg0, f32 farg0, f32 farg1);

void func_00206240(s32 a0) {
    if (func_0025FBE8(*(s32 *)((u8 *)a0 + 0x1530), (s64)1 << 46) == 0) {
        return;
    }
    func_001FBE80(a0, 3.0f, *(f32 *)D_00385940);
}
