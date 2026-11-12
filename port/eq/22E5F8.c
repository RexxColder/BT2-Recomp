#include "common.h"

s32 func_00211310(void *a0, s32 a1, s32 a2);
s32 func_0023C798(void *a0, s32 a1);
void func_002174D8(void *a0, s32 a1);
s32 func_002174B8(void *a0);
void BtlAnim_SetBlend(void *a0, f32 f12);
s32 func_0023C710(void *a0);
extern f32 D_00386718;
extern f32 D_0038671C;

s32 func_0022E5F8(void *arg0) {
    u8 *s0;
    s32 v0;
    s32 t;

    s0 = (u8 *)arg0;
    v0 = func_00211310(arg0, 2, 1);
    if (v0 != 0) {
        t = func_0023C798(s0, 0x4F);
        func_002174D8(s0, t);
    }
    if (*(s32 *)(s0 + 0x8C0) != 0) {
        return -1;
    }
    v0 = func_002174B8(s0);
    if (v0 != -1) {
        BtlAnim_SetBlend(s0, D_00386718);
        return func_002174B8(s0);
    }
    BtlAnim_SetBlend(s0, D_0038671C);
    return func_0023C710(s0);
}
