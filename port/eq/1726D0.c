#include "common.h"

void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Mtx_StoreIdentity(void *arg0);
void Mtx_RotateX(f32 farg0, void *arg1, void *arg2);
void Mtx_RotateY(f32 farg0, void *arg1, void *arg2);
void func_00129C50(void *arg0, void *arg1, void *arg2);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1, void *arg2);
extern f32 D_003848E8;
extern f32 D_003848EC;

void func_001726D0(void *arg0) {
    s32 sp[16];
    s32 sp40[16];
    u8 *s1;
    u8 *s2;
    u8 *s3;
    f32 temp_f20;
    f32 temp_f21;
    f32 f1;

    s1 = *(u8 **)((u8 *)arg0 + 0x38);
    s2 = s1 + 0x70;
    s3 = s1 + 0x40;
    Vec4_Set(s2, 0.0f, 0.0f, *(f32 *)(s1 + 0xAA0), 1.0f);
    Mtx_StoreIdentity(sp);
    Mtx_RotateY(*(f32 *)(s1 + 0xAA4), sp, sp);
    func_00129C50(s2, sp, s2);
    temp_f20 = Mathf_Asin(-*(f32 *)(s1 + 0x24));
    temp_f21 = atan2f(*(f32 *)(s1 + 0x20), *(f32 *)(s1 + 0x28));
    Mtx_RotateX(temp_f20, sp40, sp);
    Mtx_RotateY(temp_f21, sp40, sp40);
    func_00129C50(s2, sp40, s2);
    if (!(*(s32 *)s1 & 0x40)) {
        Vec3_Add(s1 + 0x80, s2, s3);
        *(s32 *)s1 = *(s32 *)s1 | 0x40;
    } else {
        Vec3_Normalize(s1 + 0x80, s2, s3);
    }
    Vec3_Add(s2, s2, s3);
    f1 = *(f32 *)(s1 + 0xAA4) + *(f32 *)(s1 + 0xAA8);
    *(f32 *)(s1 + 0xAA4) = f1;
    if (D_003848E8 < f1) {
        *(f32 *)(s1 + 0xAA4) = f1 - D_003848EC;
    }
}
