#include "common.h"

extern f32 D_00385164;
extern f32 D_00385168;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 *gBtlCamView;

void Mtx_StoreIdentity(void *m);
f32 EftMath_WrapAngle(f32 a);
void Mtx_RotateZ(void *dst, void *src, f32 angle);
void Mtx_RotateY(void *dst, void *src, f32 angle);
f32 atan2f(f32 y, f32 x);
void Vec3_Sub(void *dst, void *a, void *b);
void func_00128EF0(void);
void Vu0Cur_LoadIdentity(void);
void Vu0Cur_RotateY(f32 angle);
void func_00129028(void *p);
void Vu0Cur_MulVec4(void *dst, void *src);
void func_00128F08(void);
void Mtx_Translate(void *dst, void *src, void *v);
void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
void func_00129C50(void *dst, void *a, void *b);
void func_00129FE0(void *a, void *b, void *c, s32 d, s32 e);
s32 func_001C2848(s32 a, s32 b, s32 c);
void func_001C2878(void *buf, void *a, void *b, void *c);

void func_001C4750(u8 *arg0) {
    u8 sp[0x100];
    u8 *s0;
    u8 *s3;
    u8 *camv;
    f32 ang;
    f32 a;
    f32 b;

    s3 = arg0 + 0xE0;
    Mtx_StoreIdentity(sp);
    if (*(f32 *)(arg0 + 0x14) != 0.0f) {
        ang = EftMath_WrapAngle(*(f32 *)(arg0 + 0x14));
        *(f32 *)(arg0 + 0x14) = ang;
        Mtx_RotateZ(sp, sp, ang);
    }
    camv = gBtlCamView;
    ang = atan2f(*(f32 *)(camv + 0x8), *(f32 *)(camv + 0x28)) + D_00385164;
    if (ang != 0.0f) {
        Mtx_RotateY(sp, sp, EftMath_WrapAngle(ang));
    }
    Vec3_Sub(sp + 0xE0, arg0 + 0x20, s3);
    func_00128EF0();
    Vu0Cur_LoadIdentity();
    ang = EftMath_WrapAngle(*(f32 *)(arg0 + 0xD4));
    *(f32 *)(arg0 + 0xD4) = ang;
    Vu0Cur_RotateY(ang);
    func_00129028(s3);
    Vu0Cur_MulVec4(sp + 0xD0, sp + 0xE0);
    func_00128F08();
    Mtx_Translate(sp, sp, sp + 0xD0);
    if (arg0[1] & 2) {
        Vec4_Set(sp + 0xF0, 0.0f, -*(f32 *)(arg0 + 0x10), 0.0f, 1.0f);
        Mtx_Translate(sp, sp, sp + 0xF0);
    }

    /* four corner vectors, each built with Vec4_Set and passed through func_00129C50 */
    a = *(f32 *)(arg0 + 0x10);
    b = *(f32 *)(arg0 + 0xD8);
    Vec4_Set(sp + 0xC0, -a, -a - b, 0.0f, 1.0f);
    func_00129C50(sp + 0x40, sp, sp + 0xC0);
    Vec4_Set(sp + 0xC0, a, -a - b, 0.0f, 1.0f);
    func_00129C50(sp + 0x50, sp, sp + 0xC0);
    Vec4_Set(sp + 0xC0, -a, a, 0.0f, 1.0f);
    func_00129C50(sp + 0x60, sp, sp + 0xC0);
    Vec4_Set(sp + 0xC0, a, a, 0.0f, 1.0f);
    func_00129C50(sp + 0x70, sp, sp + 0xC0);

    func_00129FE0(sp + 0x80, gBtlCamView + 0x100, sp + 0x40, 4, 1);

    if (func_001C2848(*(s32 *)(sp + 0x80), *(s32 *)(sp + 0x84), *(s32 *)(sp + 0x88)) == 0 &&
        func_001C2848(*(s32 *)(sp + 0x90), *(s32 *)(sp + 0x94), *(s32 *)(sp + 0x98)) == 0 &&
        func_001C2848(*(s32 *)(sp + 0xA0), *(s32 *)(sp + 0xA4), *(s32 *)(sp + 0xA8)) == 0 &&
        func_001C2848(*(s32 *)(sp + 0xB0), *(s32 *)(sp + 0xB4), *(s32 *)(sp + 0xB8)) == 0) {
        s32 t;
        s32 idx;
        u8 *ptr;
        u8 *node;
        f32 x0, x1, x2, x3, f1v, f2v, f3v, f4v, tmp;
        u8 flags;

        s0 = D_00387AD8;
        D_00387AD8 = s0 + 0x90;
        *(s64 *)(s0 + 0x20) = (s64)0x5C;
        *(s64 *)(s0 + 0x00) = (s64)0xA0000008ULL;
        *(s64 *)(s0 + 0x10) = (s64)0xE400000000008001ULL;
        *(s64 *)(s0 + 0x18) = (s64)0x0042142142142160ULL;

        flags = arg0[1];
        if (flags & 1) {
            func_001C2878(s0, s3, sp + 0xD0, arg0 + 0x18);
        } else {
            s0[0x30] = arg0[0x18];
            s0[0x31] = arg0[0x19];
            s0[0x32] = arg0[0x1A];
            *(f32 *)(s0 + 0x34) = 1.0f;
            s0[0x33] = arg0[0x1B];
            s0[0x48] = arg0[0x18];
            s0[0x49] = arg0[0x19];
            s0[0x4A] = arg0[0x1A];
            *(f32 *)(s0 + 0x4C) = 1.0f;
            s0[0x4B] = arg0[0x1B];
            s0[0x60] = arg0[0x18];
            s0[0x61] = arg0[0x19];
            s0[0x62] = arg0[0x1A];
            *(f32 *)(s0 + 0x64) = 1.0f;
            s0[0x63] = arg0[0x1B];
            s0[0x78] = arg0[0x18];
            s0[0x79] = arg0[0x19];
            s0[0x7A] = arg0[0x1A];
            s0[0x7B] = arg0[0x1B];
            *(f32 *)(s0 + 0x7C) = 1.0f;
        }

        /* the 4 groups of 16-bit pairs; the 24-bit word goes to bits 32..55 of the doubleword */
        *(u16 *)(s0 + 0x40) = *(u16 *)(sp + 0x80);
        *(u16 *)(s0 + 0x42) = *(u16 *)(sp + 0x84);
        t = *(s32 *)(sp + 0x88);
        *(s64 *)(s0 + 0x40) = (*(s64 *)(s0 + 0x40) & (s64)0xFF000000FFFFFFFFULL) | ((s64)(t & 0xFFFFFF) << 32);
        s0[0x47] = 0xFF;

        *(u16 *)(s0 + 0x58) = *(u16 *)(sp + 0x90);
        *(u16 *)(s0 + 0x5A) = *(u16 *)(sp + 0x94);
        t = *(s32 *)(sp + 0x98);
        *(s64 *)(s0 + 0x58) = (*(s64 *)(s0 + 0x58) & (s64)0xFF000000FFFFFFFFULL) | ((s64)(t & 0xFFFFFF) << 32);
        s0[0x5F] = 0xFF;

        *(u16 *)(s0 + 0x70) = *(u16 *)(sp + 0xA0);
        *(u16 *)(s0 + 0x72) = *(u16 *)(sp + 0xA4);
        t = *(s32 *)(sp + 0xA8);
        *(s64 *)(s0 + 0x70) = (*(s64 *)(s0 + 0x70) & (s64)0xFF000000FFFFFFFFULL) | ((s64)(t & 0xFFFFFF) << 32);
        s0[0x77] = 0xFF;

        *(u16 *)(s0 + 0x88) = *(u16 *)(sp + 0xB0);
        *(u16 *)(s0 + 0x8A) = *(u16 *)(sp + 0xB4);
        t = *(s32 *)(sp + 0xB8);
        *(s64 *)(s0 + 0x88) = (*(s64 *)(s0 + 0x88) & (s64)0xFF000000FFFFFFFFULL) | ((s64)(t & 0xFFFFFF) << 32);
        s0[0x8F] = 0xFF;

        /* scaled byte inputs (signed) */
        x0 = (f32)(s8)arg0[0xC] * D_00385168;
        x1 = (f32)(s8)arg0[0xD] * D_00385168;
        x2 = (f32)(s8)arg0[0xE] * D_00385168;
        x3 = (f32)(s8)arg0[0xF] * D_00385168;
        f1v = x0 + x2;
        f4v = x1 + x3;
        f2v = x0;
        f3v = x1;
        if (flags & 0x10) {
            tmp = f2v;
            f2v = f1v;
            f1v = tmp;
        }
        if (flags & 0x20) {
            tmp = f3v;
            f3v = f4v;
            f4v = tmp;
        }
        *(f32 *)(s0 + 0x54) = f3v;
        *(f32 *)(s0 + 0x68) = f2v;
        *(f32 *)(s0 + 0x80) = f1v;
        *(f32 *)(s0 + 0x84) = f4v;
        *(f32 *)(s0 + 0x38) = f2v;
        *(f32 *)(s0 + 0x3C) = f3v;
        *(f32 *)(s0 + 0x50) = f1v;
        *(f32 *)(s0 + 0x6C) = f4v;

        *(s64 *)(s0 + 0x28) = *(s64 *)(*(u8 **)(arg0 + 0x8) + (arg0[3] << 4));

        t = *(s32 *)(sp + 0x88) >> 8;
        idx = arg0[2];
        if (t < 0) {
            ptr = D_00387AE0 + idx * 8;
        } else if (t < 0x1000) {
            ptr = D_00387AE0 + ((t * 2 + idx) * 8);
        } else {
            ptr = D_00387AE0 + idx * 8 + 0xFFF0;
        }
        node = *(u8 **)(ptr + 4);
        *(u8 **)(node + 4) = s0;
        *(u8 **)(ptr + 4) = s0;
    }
}
