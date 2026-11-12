#include "common.h"
#include "m2c_macros.h"

extern s32 gBtlCamView;

s32 func_0012B9B0(void);
void Vec3_Add(void *a0, void *a1, void *a2);
void Vec3_Sub(void *a0, void *a1, void *a2);
void Vec3_Cross(void *a0, void *a1, void *a2);
void Vec3_Normalize(void *a0, void *a1);
void func_00129BD0(void *a0, void *a1, f32 farg0);
s32 func_00129C28(void *a0, s32 a1);
s32 func_00129720(void *a0, void *a1, s32 a2, s32 a3);
void func_00129A50(void *a0, void *a1, void *a2, s32 a3);
void func_001296A0(void *a0, void *a1, void *a2, void *a3, s32 t0);
void func_0012DA70(void);

void func_001DD4C8(void *arg0) {
    u8 f[0x400];
    u8 *s5;
    u8 *s0;
    u8 *s1;
    u8 *s2p;
    u8 *s3p;
    u8 *s6;
    u8 *s7;
    u8 *fp;
    s32 sp400;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 i;
    s32 v;

    s5 = M2C_FIELD(arg0, u8 **, 0x38);
    sp400 = func_0012B9B0();
    s2p = s5 + 0x20;
    s1 = f + 0x260;
    func_00129C28(s1, gBtlCamView + 0x1F0);
    s0 = f + 0x270;
    s3p = s5 + 0x30;
    Vec3_Sub(s0, s2p, s1);
    Vec3_Cross(s0, s3p, s0);
    Vec3_Normalize(s0, s0);
    s1 = f + 0x280;
    func_00129BD0(s1, s0, M2C_FIELD(s5, f32 *, 0x5C));
    s6 = f + 0x1E0;
    Vec3_Add(s6, s2p, s1);
    fp = f + 0x1F0;
    Vec3_Sub(fp, s2p, s1);
    s0 = f + 0x290;
    func_00129BD0(s0, s3p, M2C_FIELD(s5, f32 *, 0x68));
    Vec3_Add(f + 0x200, s6, s0);
    Vec3_Add(f + 0x210, fp, s0);

    for (i = 0; i < 4; i++) {
        *(f32 *)(f + 0x220 + i * 16) = ((f32)(i % 2) * M2C_FIELD(s5, f32 *, 0x4C)) + M2C_FIELD(s5, f32 *, 0x90);
        *(f32 *)(f + 0x224 + i * 16) = ((f32)(i / 2) * M2C_FIELD(s5, f32 *, 0x50)) + M2C_FIELD(s5, f32 *, 0x98);
        *(f32 *)(f + 0x228 + i * 16) = 1.0f;
        *(s32 *)(f + 0x22C + i * 16) = 0;
    }
    s7 = f + 0x220;

    s1 = f + 0x3C0;
    s0 = s5 + 0x80;
    func_00129C28(s1, (s32)(s64)s0);
    func_00129C28(f + 0x3D0, (s32)(s64)s0);
    func_00129C28(f + 0x3E0, (s32)(s64)s0);
    func_00129C28(f + 0x3F0, (s32)(s64)s0);
    func_001296A0(f + 0x30, s6, s7, s1, 3);

    s2 = sp400;
    s3 = 3;
    s4 = 4;
    do {
        v = s2;
        s2 += 0x10;
        s4 -= 1;
        s3 = func_00129720(f + 0x30, f + 0x30, v, s3);
    } while (s4 >= 0);
    if (s3 != 0) {
        s0 = f + 0x2A0;
        s1 = f + 0x330;
        s4 = 2;
        func_00129A50(s0, s1, f + 0x30, s3);
        if (s4 < s3) {
            s2p = s0;
            s0 = f + 0x90;
            s7 = f + 0x50;
            do {
                v = *(s32 *)(f + 0x2A8) >> 8;
                i = s4;
                ((void (*)(void *, void *, void *, void *, void *, void *, void *, void *,
                           s64, s64, s64, s64, s64, s64))func_0012DA70)(
                    s2p, (f + 0x2A0 + i * 16) - 0x10, f + 0x2A0 + i * 16, s7,
                    s0 - 0x10, s0 + 0x20, s1, (f + 0x330 + i * 16) - 0x10,
                    (s64)(f + 0x330 + i * 16), 0, 0, 1, (s64)v,
                    M2C_FIELD(s5, s64 *, 0xC0));
                s4 += 1;
                s0 += 0x30;
            } while (s4 < s3);
        }
    }

    func_001296A0(f + 0x30, fp, f + 0x230, f + 0x3D0, 3);

    s2 = sp400;
    s3 = 3;
    s4 = 4;
    do {
        v = s2;
        s2 += 0x10;
        s4 -= 1;
        s3 = func_00129720(f + 0x30, f + 0x30, v, s3);
    } while (s4 >= 0);
    if (s3 != 0) {
        s0 = f + 0x2A0;
        s1 = f + 0x330;
        func_00129A50(s0, s1, f + 0x30, s3);
        s4 = 2;
        if (s4 < s3) {
            s2p = s0;
            s0 = f + 0x90;
            s7 = f + 0x50;
            do {
                v = *(s32 *)(f + 0x2A8) >> 8;
                i = s4;
                ((void (*)(void *, void *, void *, void *, void *, void *, void *, void *,
                           s64, s64, s64, s64, s64, s64))func_0012DA70)(
                    s2p, (f + 0x2A0 + i * 16) - 0x10, f + 0x2A0 + i * 16, s7,
                    s0 - 0x10, s0 + 0x20, s1, (f + 0x330 + i * 16) - 0x10,
                    (s64)(f + 0x330 + i * 16), 0, 0, 1, (s64)v,
                    M2C_FIELD(s5, s64 *, 0xC0));
                s4 += 1;
                s0 += 0x30;
            } while (s4 < s3);
        }
    }
}
