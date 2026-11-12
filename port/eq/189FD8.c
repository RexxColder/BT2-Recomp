#include "common.h"

void Vec4_Set(void *v, f32 x, f32 y, f32 z, f32 w);
void Mtx_StoreIdentity(void *m);
void Mtx_Translate(void *dst, void *src, void *v);
void Mtx_RotateX(f32 a, void *dst, void *src);
void Mtx_RotateY(f32 a, void *dst, void *src);
void Mtx_RotateZ(f32 a, void *dst, void *src);
void func_00128C28(void *dst, void *src, void *v);
void func_00128C58(f32 a, void *dst, void *src);
void func_00129C50(void *a, void *b, void *c);
void func_00129BD0(void *b, void *c, f32 a);
f32 Mathf_Asin(f32 a);
f32 EftMath_WrapAngle(f32 a);
f32 atan2f(f32 y, f32 x);

void func_00189FD8(u8 *arg0, s64 *arg1, s64 *arg2, s64 *arg3, f32 farg0, f32 farg1, f32 farg2) {
    s64 sp[16];
    u8 *p;
    s32 i;
    f32 *m;
    f32 *vA;
    f32 *v60;
    f32 *v70;
    f32 temp_f20;
    f32 temp_f21;

    m = (f32 *)sp;
    vA = (f32 *)((u8 *)sp + 0x40);
    v60 = (f32 *)((u8 *)sp + 0x60);
    v70 = (f32 *)((u8 *)sp + 0x70);

    /* local matrix copy (8 dwords) and two 16-byte vector copies */
    sp[0] = arg1[0];
    sp[1] = arg1[1];
    sp[2] = arg1[2];
    sp[3] = arg1[3];
    sp[4] = arg1[4];
    sp[5] = arg1[5];
    sp[6] = arg1[6];
    sp[7] = arg1[7];
    sp[8] = arg2[0];
    sp[9] = arg2[1];
    sp[10] = arg3[0];
    sp[11] = arg3[1];

    Vec4_Set(arg0 + 0x40, -1.0f, -1.0f, 0.0f, 1.0f);
    Vec4_Set(arg0 + 0x50, -1.0f, 1.0f, 0.0f, 1.0f);
    Vec4_Set(arg0 + 0x60, 1.0f, -1.0f, 0.0f, 1.0f);
    Vec4_Set(arg0 + 0x70, 1.0f, 1.0f, 0.0f, 1.0f);
    Vec4_Set((u8 *)sp + 0x70, *(f32 *)(arg0 + 0x88) * 0.5f, *(f32 *)(arg0 + 0x8C) * 0.5f, 1.0f, 1.0f);
    Vec4_Set((u8 *)sp + 0x60, v70[0] * farg1, v70[1] * farg2, 0.0f, 1.0f);
    Mtx_Translate(m, m, v60);
    func_00128C28(m, m, v70);
    func_00128C58(farg0, m, m);
    Mtx_RotateZ(*(f32 *)(arg0 + 0xA4), m, m);
    Mtx_RotateX(*(f32 *)(arg0 + 0xA0), m, m);
    Mtx_RotateZ(*(f32 *)(arg0 + 0xAC), m, m);

    p = arg0 + 0x40;
    for (i = 0; i < 4; i++) {
        func_00129C50(p, m, p);
        p += 0x10;
    }

    Mtx_StoreIdentity(m);
    func_00129BD0(vA, vA, -1.0f);
    temp_f21 = EftMath_WrapAngle(Mathf_Asin(-vA[1]));
    temp_f20 = EftMath_WrapAngle(atan2f(vA[0], vA[2]));
    Mtx_RotateX(temp_f21, m, m);
    Mtx_RotateY(temp_f20, m, m);
    Mtx_Translate(m, m, arg0);

    p = arg0 + 0x40;
    for (i = 0; i < 4; i++) {
        func_00129C50(p, m, p);
        p += 0x10;
    }
}
