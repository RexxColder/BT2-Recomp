#include "common.h"

void Mtx_StoreIdentity(s32 a0);
void func_00208BE0(s32 a0, void *a1, s32 a2);
f32 func_00208D50(s32 a0);
void func_00208DE8(s32 a0, void *a1, s32 a2);
void func_002088F0(s32 a0, void *a1);
void Vec3_Normalize(void *a0, void *a1);
void Vec3_Sub(void *a0, void *a1, void *a2);
f32 Mathf_Asin(f32 f12);
void Mtx_RotateX(f32 f12, s32 a0, s32 a1);
void Mtx_RotateY(f32 f12, s32 a0, s32 a1);
f32 atan2f(f32 f12, f32 f13);
extern f32 D_00384CC4;
extern f32 D_00384CC8;

void EftGlow_CalcFrame(s32 arg0, s32 arg1, s32 arg2) {
    f32 sp[4];
    f32 sp10[4];
    f32 sp20[4];
    f32 t;

    Mtx_StoreIdentity(arg0);
    if (arg2 != 5) {
        func_00208BE0(arg1, sp, 0x2E);
        if (arg2 == 3) {
            t = func_00208D50(arg1) - 1.0f;
            sp[1] = sp[1] + t;
        } else if (arg2 == 4) {
            t = func_00208D50(arg1) + 1.0f;
            sp[1] = sp[1] + t;
        }
        Vec3_Normalize(sp, sp);
        sp20[0] = Mathf_Asin(sp[1]);
        Mtx_RotateX(sp20[0], arg0, arg0);
        func_002088F0(arg1, sp20);
        t = sp20[1] + D_00384CC4;
        sp20[1] = t;
        if (D_00384CC4 < t) {
            sp20[1] = t - D_00384CC8;
        }
        Mtx_RotateY(sp20[1], arg0, arg0);
        return;
    }
    func_00208DE8(arg1, sp10, 0x2E);
    func_00208DE8(arg1, sp, 3);
    Vec3_Sub(sp, sp, sp10);
    Vec3_Normalize(sp, sp);
    sp20[0] = Mathf_Asin(-sp[1]);
    sp20[1] = atan2f(sp[0], sp[2]);
    Mtx_RotateX(sp20[0], arg0, arg0);
    Mtx_RotateY(sp20[1], arg0, arg0);
}
