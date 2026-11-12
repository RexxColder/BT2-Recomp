#include "common.h"

s32 EftShot_TestBits(s32 a0, s32 a1);
void func_00129C28(u8 *a0, u8 *a1);
void func_001EDBD8(s32 a0, s32 a1);
void Mtx_StoreIdentity(u8 *a0);
f32 EftMath_WrapAngle(f32 farg0);
void Mtx_RotateX(u8 *a0, u8 *a1, f32 farg0);
void Mtx_RotateY(u8 *a0, u8 *a1, f32 farg0);
void Mtx_Translate(u8 *a0, u8 *a1, u8 *a2);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 y, f32 x);
void func_001EDD40(s32 a0, u8 *a1);
extern f32 D_0038473C;

void func_001601F8(u8 *arg0) {
    u8 *p;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    f32 f20;
    f32 f21;

    p = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(p + 0x100);
    s3 = p + 0x70;
    s1 = p + 0x30;

    if (EftShot_TestBits(*(s32 *)s2, 2) != 0) {
        func_00129C28(s3, p + 0x90);
        *(s32 *)(p + 0x4) |= 1;
    }
    if (EftShot_TestBits(*(s32 *)s2, 4) != 0) {
        func_00129C28(s3, p + 0x90);
        func_001EDBD8(*(s32 *)(p + 0x8), 1);
        *(s32 *)(p + 0x4) |= 2;
    }
    if (*(s32 *)p & 5) {
        func_001EDBD8(*(s32 *)(p + 0x8), 0);
        *(s32 *)(p + 0x4) |= 4;
    }
    Mtx_StoreIdentity(s1);
    Mtx_RotateY(s1, s1, EftMath_WrapAngle(D_0038473C));
    f20 = Mathf_Asin(-*(f32 *)(p + 0x84));
    f21 = atan2f(*(f32 *)(p + 0x80), *(f32 *)(p + 0x88));
    Mtx_RotateX(s1, s1, EftMath_WrapAngle(f20));
    Mtx_RotateY(s1, s1, EftMath_WrapAngle(f21));
    if (*(s32 *)(p + 0x4) & 2) {
        func_00129C28(s3, p + 0xD0);
    }
    Mtx_Translate(s1, s1, s3);
    func_001EDD40(*(s32 *)(p + 0x8), s1);
}
