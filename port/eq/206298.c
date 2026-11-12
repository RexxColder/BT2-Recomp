#include "common.h"

/* 0x00206298: if (func_0025FBE8(a0->+0x1530, 1 << 45)) tail BtlChar_Vibrate(a0, 1.0f, *(f32 *)D_00385944). */
extern u8 D_00385944[];
s32 func_0025FBE8(s32 arg0, s64 arg1);
void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);

void func_00206298(s32 a0) {
    if (func_0025FBE8(*(s32 *)((u8 *)a0 + 0x1530), (s64)1 << 45) == 0) {
        return;
    }
    BtlChar_Vibrate(a0, 1.0f, *(f32 *)D_00385944);
}
