#include "common.h"

void func_00208860(s32 arg0, s32 arg1);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
f32 func_00129CD8(s32 arg0, s32 arg1);

/* 0x001EEE50 EftVolleyAim_GetFighterDistSq (BT3 exact): a = base pos of fighter 0, b = of fighter 1, d = a - b,
 * returns Vec3_Dot(d, d) (func_00129CD8). */
f32 EftVolleyAim_GetFighterDistSq(void) {
    f32 a[4];
    f32 b[4];
    f32 d[4];

    func_00208860(0, (s32)a);
    func_00208860(1, (s32)b);
    func_00129B58((s32)d, (s32)a, (s32)b);
    return func_00129CD8((s32)d, (s32)d);
}
