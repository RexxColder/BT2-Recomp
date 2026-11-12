#include "common.h"

extern u8 *gEftBound;
extern u8 *D_003876A0;
extern f32 D_00384518;
extern f32 D_0038451C;
extern f32 D_00384520;
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 sqrtf(f32 x);
extern f32 fabsf(f32 x);
void Vec3_Sub(void *dst, void *a, void *b);
void Vec3_Cross(void *dst, void *a, void *b);
void Vec3_Normalize(void *dst, void *src);
s32 BtlCharApi_IsInTechnique();
s32 func_0020A758();
s32 func_0020A7D0();

s32 func_00144258(u8 *arg0, u8 *arg1) {
    u64 spq[10];
    u8 *sp = (u8 *)spq;
    u8 *s2 = arg0 + 0x30;
    u8 *s0, *s6, *s1, *s3, *a2, *v;
    f32 f0, f1, f2, f3, f4, f20, f21, f22, f23, f24, f25, f12;
    s32 s4, s5, v0, a1, t0, a0, i, ret;
    s16 cnt;

    s0 = *(u8 **)(gEftBound + 0x218);
    s6 = *(u8 **)(gEftBound + 0x21C);
    f20 = 1.0f;
    *(f32 *)(s2 + 0x20) = sinf(*(f32 *)(arg0 + 0x10)) * *(f32 *)(arg0 + 4);
    *(f32 *)(s2 + 0x24) = *(f32 *)(arg0 + 0x24);
    f0 = cosf(*(f32 *)(arg0 + 0x10));
    *(f32 *)(s2 + 0x2C) = f20;
    *(f32 *)(s2 + 0x28) = f0 * *(f32 *)(arg0 + 4);
    Vec3_Sub(sp, arg0 + 0x50, arg0 + 0x20);
    f1 = *(f32 *)(sp + 0);
    f0 = *(f32 *)(sp + 8);
    f12 = f1 * f1 + f0 * f0;
    f2 = sqrtf(f12);
    *(f32 *)(s2 + 4) = f2;
    f0 = f2 - *(f32 *)(arg0 + 0x18);
    *(f32 *)(s2 + 4) = f0;
    if (f0 < 0.0f) *(f32 *)(s2 + 4) = 0.0f;
    f1 = *(f32 *)s0;
    f0 = *(f32 *)(s2 + 4);
    f22 = (f1 - f0) / f1;
    if (f22 < 0.0f) f22 = 0.0f;

    if (!(*(u64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        f0 = *(f32 *)(s2 + 0x18) + *(f32 *)(s0 + 0x2C);
        *(f32 *)(s2 + 0x18) = f0;
        if (f20 < f0) *(f32 *)(s2 + 0x18) = f0 - f20;
        f0 = *(f32 *)(s2 + 0x1C) + *(f32 *)(s0 + 0x30);
        *(f32 *)(s2 + 0x1C) = f0;
        if (f20 < f0) *(f32 *)(s2 + 0x1C) = f0 - f20;
        f0 = *(f32 *)(s0 + 0x34);
        f3 = D_00384518;
        f2 = *(f32 *)(s2 + 0x14);
        f0 = f0 * f3;
        f1 = D_0038451C;
        f2 = f2 + f0;
        *(f32 *)(s2 + 0x14) = f2;
        if (f2 < f1) {
            *(f32 *)(s2 + 0x14) = f2 + f3;
        } else {
            f0 = D_00384520;
            if (f0 < f2) *(f32 *)(s2 + 0x14) = f2 - f3;
        }
    }
    if (BtlCharApi_IsInTechnique(*(s32 *)arg1) || func_0020A758(*(s32 *)arg1) ||
        func_0020A7D0(*(s32 *)arg1)) {
        f22 = 0.0f;
    }
    if (!(0.0f < f22)) {
        *(u8 *)s2 = 0;
        return 1;
    }
    *(u8 *)s2 = 1;
    s5 = 0;
    *(f32 *)(s2 + 0xC) = 6.0f;
    *(f32 *)(s2 + 8) = *(f32 *)(s0 + 0x1C);
    *(f32 *)(s2 + 0x10) = 4.0f;
    f25 = *(f32 *)(arg0 + 0x24) - *(f32 *)(s0 + 4) * 0.5f;
    f24 = fabsf(cosf(*(f32 *)(s2 + 0x14)));
    if ((s32)*(f32 *)(s2 + 0x10) > 0) {
        do {
            f4 = *(f32 *)(s2 + 0xC);
            if ((s32)f4 > 0) {
                f23 = (f32)s5;
                f21 = 1.0f;
                s4 = 0;
                do {
                    f3 = f4 - f21;
                    f1 = *(f32 *)(s2 + 8);
                    f2 = (f32)s4;
                    v0 = (s32)f4;
                    f20 = *(f32 *)(arg0 + 0x10);
                    f0 = f1 * 0.5f;
                    f2 = f2 / f3;
                    v0 = s5 * v0 + s4;
                    s4++;
                    f20 = f20 - f0;
                    s1 = s2 + (v0 << 6) + 0x30;
                    f1 = f1 * f2;
                    f20 = f20 + f1;
                    *(f32 *)s1 = sinf(f20) * *(f32 *)(arg0 + 4);
                    f0 = cosf(f20);
                    f1 = *(f32 *)(arg0 + 4);
                    f12 = *(f32 *)s1;
                    *(f32 *)(s1 + 8) = f0 * f1;
                    f0 = *(f32 *)(s2 + 0x10);
                    f1 = *(f32 *)(s0 + 4);
                    f0 = f0 - f21;
                    *(f32 *)(s1 + 0xC) = f21;
                    f0 = f23 / f0;
                    f0 = f0 * f1;
                    f0 = f25 + f0;
                    *(f32 *)(s1 + 4) = f0;
                    f1 = *(f32 *)(s0 + 0x20);
                    f3 = *(f32 *)(s0 + 0x24);
                    f20 = f20 / f1;
                    f1 = *(f32 *)(s2 + 0x1C);
                    f2 = *(f32 *)(s2 + 0x18);
                    *(f32 *)(s1 + 0x28) = f21;
                    *(s32 *)(s1 + 0x2C) = 0;
                    f0 = f0 / f3;
                    f2 = f2 + f20;
                    *(f32 *)(s1 + 0x20) = f2;
                    f1 = f1 + f0;
                    *(f32 *)(s1 + 0x24) = f1;
                    f0 = *(f32 *)(s2 + 0x20);
                    f2 = *(f32 *)(s2 + 0x24);
                    f12 = f12 - f0;
                    f3 = *(f32 *)(s2 + 0x28);
                    *(f32 *)(sp + 0) = f12;
                    f12 = f12 * f12;
                    f1 = *(f32 *)(s1 + 4);
                    f1 = f1 - f2;
                    *(f32 *)(sp + 4) = f1;
                    f1 = f1 * f1;
                    f0 = *(f32 *)(s1 + 8);
                    f0 = f0 - f3;
                    f12 = f12 + f1;
                    f2 = f0 * f0;
                    *(f32 *)(sp + 8) = f0;
                    f12 = f12 + f2;
                    f0 = sqrtf(f12);
                    f1 = *(f32 *)(s0 + 0x18);
                    f0 = f1 - f0;
                    f12 = f0 / f1;
                    if (f12 < 0.0f) {
                        f12 = 0.0f;
                    } else if (f21 < f12) {
                        f12 = 1.0f;
                    }
                    *(f32 *)(s1 + 0x30) = *(f32 *)(s6 + 0);
                    *(f32 *)(s1 + 0x34) = *(f32 *)(s6 + 4);
                    *(f32 *)(s1 + 0x38) = *(f32 *)(s6 + 8);
                    f0 = *(f32 *)(s0 + 0x14);
                    f0 = f0 * f22;
                    f0 = f0 * f12;
                    f1 = f0 * f24;
                    f0 = f0 + f1;
                    *(f32 *)(s1 + 0x3C) = f0;
                    if (255.0f < f0) *(f32 *)(s1 + 0x3C) = 255.0f;
                    f4 = *(f32 *)(s2 + 0xC);
                } while (s4 < (s32)f4);
            }
            s5++;
        } while (s5 < (s32)*(f32 *)(s2 + 0x10));
    }
    a0 = (s32)*(f32 *)(s2 + 0xC);
    a1 = (s32)*(f32 *)(s2 + 0xC);
    *(s32 *)(sp + 0x14) = 1;
    *(s32 *)(sp + 0x10) = 0;
    t0 = 0;
    a0 = a0 - 1;
    a0 = a0 * ((s32)*(f32 *)(s2 + 0x10) - 1);
    *(s32 *)(sp + 0x1C) = a1 + 1;
    *(s32 *)(sp + 0x18) = a1;
    *(s16 *)(s2 + 2) = (s16)a0;
    cnt = *(s16 *)(s2 + 2);
    ret = (s32)((u32)a0 << 16);
    if (cnt > 0) {
        a2 = s2;
        for (i = 0; i < *(s16 *)(s2 + 2); i++) {
            s32 rem, k;
            *(u64 *)(a2 + 0x630) = *(u64 *)(sp + 0x10);
            *(u64 *)(a2 + 0x638) = *(u64 *)(sp + 0x18);
            rem = (t0 + 1) % ((s32)*(f32 *)(s2 + 0xC) - 1);
            t0 = rem;
            for (k = 0; k < 4; k++) {
                *(s32 *)(sp + 0x10 + k * 4) += rem ? 1 : 2;
            }
            a2 += 0x20;
        }
        ret = (s32)((u32)*(u16 *)(s2 + 2) << 16);
    }
    s1 = s2 + 0x30;
    s4 = 0;
    if (ret > 0) {
        s3 = s2;
        do {
            v0 = 0;
            *(u64 *)(sp + 0x40) = *(u64 *)(s3 + 0x630);
            *(s32 *)(sp + 0x48) = *(s32 *)(s3 + 0x638);
            v = s3 + 0x640;
            s4++;
            s3 += 0x20;
            Vec3_Sub(sp + 0x20, s1 + (*(s32 *)(sp + 0x44) << 6), s1 + (*(s32 *)(sp + 0x40) << 6));
            Vec3_Sub(sp + 0x30, s1 + (*(s32 *)(sp + 0x48) << 6), s1 + (*(s32 *)(sp + 0x44) << 6));
            Vec3_Cross(v, sp + 0x30, sp + 0x20);
            Vec3_Normalize(v, v);
            ret = (s4 < *(s16 *)(s2 + 2));
        } while (s4 < *(s16 *)(s2 + 2));
    }
    return ret;
}
