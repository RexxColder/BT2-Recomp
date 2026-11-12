#include "common.h"

s32 func_0025FBE8(s32 arg0, s64 arg1);
void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00385940;

/* if func_0025FBE8(obj->+0x1530, 1 << 46) is nonzero: func_001FBE80(obj, 3.0f, D_00385940) (tail call) */
void func_00206240(s32 arg0) {
    if (func_0025FBE8(*(s32 *)((u8 *)arg0 + 0x1530), (s64)0x8000 << 31) != 0) {
        func_001FBE80(arg0, 3.0f, D_00385940);
    }
}
