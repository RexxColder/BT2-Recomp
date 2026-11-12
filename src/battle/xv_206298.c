#include "common.h"

s32 func_0025FBE8(s32 arg0, s64 arg1);
void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00385944;

/* if func_0025FBE8(obj->+0x1530, 1 << 45) is nonzero: BtlChar_Vibrate(obj, 1.0f, D_00385944) (tail call) */
void func_00206298(s32 arg0) {
    if (func_0025FBE8(*(s32 *)((u8 *)arg0 + 0x1530), (s64)0x8000 << 30) != 0) {
        BtlChar_Vibrate(arg0, 1.0f, D_00385944);
    }
}
