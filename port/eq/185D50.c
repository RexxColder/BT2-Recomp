#include "common.h"

extern void Vec4_Set();
f32 EftMath_WrapAngle(f32 a);
f32 Mathf_Asin(f32 a);
f32 atan2f(f32 y, f32 x);
void Mtx_RotateX(f32 a, void *m, void *t);
void Mtx_RotateY(f32 a, void *m, void *t);
void Mtx_RotateZ(f32 a, void *m, void *t);
void Mtx_StoreIdentity(void *m);
void Mtx_Translate(void *dst, void *src, void *v);
void func_00128C28(void *a, void *b, void *c);
void func_00128C58(f32 a, void *b, void *c);
void func_00129BD0(void *a, void *b, f32 c);
void func_00129C50(void *a, void *b, void *c);

void func_00185D50(void *arg0, void *arg1, void *arg2, void *arg3, f32 fa, f32 fb, f32 fc) {
    u8 sp[0x80];
    u8 *s0;
    u8 *s3;
    s32 s6;
    f32 temp_f20;
    f32 temp_f21;

    /* copy of arg1 (64 bytes) at sp+0..0x40, then arg2 and arg3 (16 bytes each) */
    *(s64 *)(sp + 0x00) = *(s64 *)((u8 *)arg1 + 0x00);
    *(s64 *)(sp + 0x08) = *(s64 *)((u8 *)arg1 + 0x08);
    *(s64 *)(sp + 0x10) = *(s64 *)((u8 *)arg1 + 0x10);
    *(s64 *)(sp + 0x18) = *(s64 *)((u8 *)arg1 + 0x18);
    *(s64 *)(sp + 0x20) = *(s64 *)((u8 *)arg1 + 0x20);
    *(s64 *)(sp + 0x28) = *(s64 *)((u8 *)arg1 + 0x28);
    *(s64 *)(sp + 0x30) = *(s64 *)((u8 *)arg1 + 0x30);
    *(s64 *)(sp + 0x38) = *(s64 *)((u8 *)arg1 + 0x38);
    *(s64 *)(sp + 0x40) = *(s64 *)((u8 *)arg2 + 0x00);
    *(s64 *)(sp + 0x48) = *(s64 *)((u8 *)arg2 + 0x08);
    *(s64 *)(sp + 0x50) = *(s64 *)((u8 *)arg3 + 0x00);
    *(s64 *)(sp + 0x58) = *(s64 *)((u8 *)arg3 + 0x08);

    ((void (*)(void *, s64, void *, s64, f32, f32, f32, f32))Vec4_Set)(
        (u8 *)arg0 + 0x40, *(s64 *)((u8 *)arg2 + 0x00), arg2, *(s64 *)((u8 *)arg2 + 0x08),
        -1.0f, -1.0f, 0.0f, 1.0f);
    ((void (*)(void *, f32, f32, f32, f32))Vec4_Set)((u8 *)arg0 + 0x50, -1.0f, 1.0f, 0.0f, 1.0f);
    ((void (*)(void *, f32, f32, f32, f32))Vec4_Set)((u8 *)arg0 + 0x60, 1.0f, -1.0f, 0.0f, 1.0f);
    ((void (*)(void *, f32, f32, f32, f32))Vec4_Set)((u8 *)arg0 + 0x70, 1.0f, 1.0f, 0.0f, 1.0f);
    ((void (*)(void *, f32, f32, f32, f32))Vec4_Set)(sp + 0x70,
        *(f32 *)((u8 *)arg0 + 0x88) * 0.5f, *(f32 *)((u8 *)arg0 + 0x8C) * 0.5f, 1.0f, 1.0f);
    ((void (*)(void *, f32, f32, f32, f32))Vec4_Set)(sp + 0x60,
        *(f32 *)(sp + 0x70) * fb, *(f32 *)(sp + 0x74) * fc, 0.0f, 1.0f);

    Mtx_Translate(sp, sp, sp + 0x60);
    func_00128C28(sp, sp, sp + 0x70);
    func_00128C58(fa, sp, sp);
    Mtx_RotateZ(*(f32 *)((u8 *)arg0 + 0xA4), sp, sp);
    Mtx_RotateX(*(f32 *)((u8 *)arg0 + 0xA0), sp, sp);
    Mtx_RotateZ(*(f32 *)((u8 *)arg0 + 0xAC), sp, sp);

    s3 = (u8 *)arg0 + 0x40;
    s6 = 3;
    do {
        s6 -= 1;
        func_00129C50(s3, sp, s3);
        s3 += 0x10;
    } while (s6 >= 0);

    Mtx_StoreIdentity(sp);
    s0 = (u8 *)arg0 + 0x40;
    func_00129BD0(sp + 0x50, sp + 0x50, -1.0f);
    temp_f21 = EftMath_WrapAngle(Mathf_Asin(-*(f32 *)(sp + 0x54)));
    temp_f20 = EftMath_WrapAngle(atan2f(*(f32 *)(sp + 0x50), *(f32 *)(sp + 0x58)));
    Mtx_RotateX(temp_f21, sp, sp);
    Mtx_RotateY(temp_f20, sp, sp);
    Mtx_Translate(sp, sp, arg0);

    s6 = 3;
    do {
        s6 -= 1;
        func_00129C50(s0, sp, s0);
        s0 += 0x10;
    } while (s6 >= 0);
}
