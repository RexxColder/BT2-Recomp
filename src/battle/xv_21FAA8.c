#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00215E30(s32 arg0, f32 farg0, f32 farg1);

/* if func_00211310(arg0, 6, 1) is nonzero: func_00215E30(arg0, +0xB64 float, +0xB68 float) */
void func_0021FAA8(s32 arg0) {
    if (func_00211310(arg0, 6, 1) != 0) {
        func_00215E30(arg0, *(f32 *)((u8 *)arg0 + 0xB64), *(f32 *)((u8 *)arg0 + 0xB68));
    }
}
