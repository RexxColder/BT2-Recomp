#include "common.h"

extern f32 D_00386C00;
extern s32 func_00211310(s32 a0, s32 a1, s32 a2);
extern s32 func_00212320(s32 a0);
extern s32 func_00241F80(s32 a0, s32 a1);
extern void func_0023AAA0(s32 a0);
extern void BtlAnim_SetBlend(s32 a0, f32 f);
extern s32 func_0023C710(s32 a0);

s32 func_0023B5C0(s32 obj) {
    s32 v;

    if (func_00211310(obj, 2, 1) == 0) {
        return -1;
    }
    v = func_00212320(obj);
    if (func_00241F80(obj, v) & 0x80) {
        func_0023AAA0(obj);
    }
    BtlAnim_SetBlend(obj, D_00386C00);
    return func_0023C710(obj);
}
