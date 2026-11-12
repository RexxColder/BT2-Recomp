#include "common.h"

f32 EftMath_WrapAngle(f32 farg0);
void Mtx_Mul(s32 arg0, s32 arg1, s32 arg2);
void Mtx_RotateX(f32 farg0, s32 arg0, s32 arg1);
void Mtx_StoreIdentity(s32 arg0);
void Vec4_Set(f32 farg0, f32 farg1, f32 farg2, f32 farg3, s32 arg0);
void func_00128810(s32 arg0, s32 arg1);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_001EDD40(s32 arg0, s32 arg1);

void func_001AD0E0(void *arg0) {
    u8 *s1;
    s32 t;
    f32 m[16];
    f32 mb[16];
    f32 v[4];

    s1 = *(u8 **)((u8 *)arg0 + 0x38);
    t = *(s32 *)(s1 + 0x11C);
    if (t == -1) {
        return;
    }
    if (*(s32 *)(s1 + 0xC0) & 0x40) {
        func_001EDBD8(t, 1);
    } else {
        func_001EDBD8(t, 0);
    }

    Mtx_StoreIdentity((s32)m);
    Mtx_StoreIdentity((s32)mb);
    mb[0] = *(f32 *)(s1 + 0xD0) * 3.5f;
    mb[5] = *(f32 *)(s1 + 0xD0) * 3.5f;
    mb[10] = *(f32 *)(s1 + 0xD0) * 3.5f;
    Mtx_Mul((s32)m, (s32)m, (s32)mb);
    Mtx_RotateX(EftMath_WrapAngle(-*(f32 *)(s1 + 0xD8)), (s32)m, (s32)m);
    Vec4_Set(*(f32 *)(s1 + 0x50), *(f32 *)(s1 + 0x54) + 1.5f, *(f32 *)(s1 + 0x58), 1.0f, (s32)v);
    func_00128810((s32)m, (s32)v);
    func_001EDD40(*(s32 *)(s1 + 0x11C), (s32)m);
}
