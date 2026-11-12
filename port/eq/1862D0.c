#include "common.h"

extern s32 gBtlCamView;
extern void Vec4_Set();
f32 EftMath_WrapAngle(f32 a);
f32 Mathf_Asin(f32 a);
f32 atan2f(f32 y, f32 x);
void Mtx_RotateX(f32 a, void *m, void *t);
void Mtx_RotateY(f32 a, void *m, void *t);
void Mtx_RotateZ(f32 a, void *m, void *t);
void Mtx_Translate(void *dst, void *src, void *v);
void Vec3_Add(void *dst, void *a, void *b);
void Vec3_Sub(void *dst, void *a, s32 b);
void func_00128C58(void *a, void *b, f32 f);
void func_00129BD0(void *out, void *obj, f32 f);
void func_00129C50(void *a, void *b, void *c);

s32 func_001862D0(void *arg0, void *arg1, void *arg2, f32 fa, f32 fb, f32 fc) {
    u8 sp[0x90];
    f32 s;
    f32 ns;
    f32 temp_f21;
    f32 temp_f20_2;

    s = *(f32 *)((u8 *)arg0 + 0x88) * 0.5f;
    ns = -s;

    /* copy of arg1 (64 bytes) at sp+0..0x40 */
    *(s64 *)(sp + 0x00) = *(s64 *)((u8 *)arg1 + 0x00);
    *(s64 *)(sp + 0x08) = *(s64 *)((u8 *)arg1 + 0x08);
    *(s64 *)(sp + 0x10) = *(s64 *)((u8 *)arg1 + 0x10);
    *(s64 *)(sp + 0x18) = *(s64 *)((u8 *)arg1 + 0x18);
    *(s64 *)(sp + 0x20) = *(s64 *)((u8 *)arg1 + 0x20);
    *(s64 *)(sp + 0x28) = *(s64 *)((u8 *)arg1 + 0x28);
    *(s64 *)(sp + 0x30) = *(s64 *)((u8 *)arg1 + 0x30);
    *(s64 *)(sp + 0x38) = *(s64 *)((u8 *)arg1 + 0x38);

    /* copy of arg2 (16 bytes) at sp+0x40 */
    *(s64 *)(sp + 0x40) = *(s64 *)((u8 *)arg2 + 0);
    *(s64 *)(sp + 0x48) = *(s64 *)((u8 *)arg2 + 8);

    ((void (*)(void *, void *, s64, s64, s64, s64, s64, s64, f32, f32, f32, f32))Vec4_Set)(
        sp + 0x70, arg1,
        *(s64 *)((u8 *)arg1 + 0x20), *(s64 *)((u8 *)arg1 + 0x18),
        *(s64 *)((u8 *)arg1 + 0x08), *(s64 *)((u8 *)arg1 + 0x10),
        *(s64 *)((u8 *)arg1 + 0x00), *(s64 *)((u8 *)arg1 + 0x38),
        fb * s, 0.0f, fc * s, 1.0f);
    func_00129BD0(sp + 0x50, arg0, fa);
    Vec3_Add(sp + 0x60, sp + 0x50, sp + 0x40);
    Vec3_Sub(sp + 0x80, sp + 0x60, gBtlCamView + 0x1F0);

    ((void (*)(void *, f32, f32, f32, f32))Vec4_Set)((u8 *)arg0 + 0x40, ns, 0.0f, ns, 1.0f);
    ((void (*)(void *, f32, f32, f32, f32))Vec4_Set)((u8 *)arg0 + 0x50, ns, 0.0f, s, 1.0f);
    ((void (*)(void *, f32, f32, f32, f32))Vec4_Set)((u8 *)arg0 + 0x60, s, 0.0f, ns, 1.0f);
    ((void (*)(void *, f32, f32, f32, f32))Vec4_Set)((u8 *)arg0 + 0x70, s, 0.0f, s, 1.0f);

    Mtx_Translate(sp, sp, sp + 0x70);
    func_00128C58(sp, sp, fa);
    Mtx_RotateY(EftMath_WrapAngle(*(f32 *)((u8 *)arg0 + 0xA4) + *(f32 *)((u8 *)arg0 + 0xAC)), sp, sp);
    Mtx_RotateZ(EftMath_WrapAngle(atan2f(*(f32 *)(sp + 0x80), *(f32 *)(sp + 0x84))), sp, sp);
    temp_f21 = EftMath_WrapAngle(Mathf_Asin(-*(f32 *)((u8 *)arg0 + 0x14)));
    temp_f20_2 = EftMath_WrapAngle(atan2f(*(f32 *)((u8 *)arg0 + 0x10), *(f32 *)((u8 *)arg0 + 0x18)));
    Mtx_RotateX(temp_f21, sp, sp);
    Mtx_RotateY(temp_f20_2, sp, sp);
    Mtx_Translate(sp, sp, sp + 0x50);
    Mtx_Translate(sp, sp, sp + 0x40);
    func_00129C50((u8 *)arg0 + 0x40, sp, (u8 *)arg0 + 0x40);
    func_00129C50((u8 *)arg0 + 0x50, sp, (u8 *)arg0 + 0x50);
    func_00129C50((u8 *)arg0 + 0x60, sp, (u8 *)arg0 + 0x60);
    func_00129C50((u8 *)arg0 + 0x70, sp, (u8 *)arg0 + 0x70);
    return 1;
}
