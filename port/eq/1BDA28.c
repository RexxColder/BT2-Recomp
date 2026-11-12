#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define S32(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern f32 D_00385138;
extern f32 D_0038513C;
extern f32 D_00385140;
extern f32 D_00385144;

void Vec3_Set(void *a0, f32 f12, f32 f13, f32 f14);
void Vec3_Add(void *a0, void *a1, void *a2);
void Vec3_Normalize(void *a0, void *a1);
void Mtx_RotateZ(f32 f12, void *a0, void *a1);
void func_00129C50(void *a0, void *a1, void *a2);
void func_0012A360(f32 f12, void *a0, void *a1, void *a2, s32 a3);
void func_00129B28(void *a0, void *a1, void *a2);
void func_00129D68(void *a0, void *a1, f32 f12, f32 f13);
void func_001BD900(void *a0, void *a1);
void func_001BCD58(void *a0);
void func_001BCDA0(void *a0, void *a1);
s32 rand(void);

void func_001BDA28(u8 *arg0, u8 *arg1, s32 arg3) {
    u8 sp[0x60];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s6;
    u8 *s7;
    f32 f20;
    f32 sum;
    f32 f0;
    f32 f1;
    s32 v1;
    s32 r;

    s3 = *(u8 **)(arg1 + 0x38);
    s7 = sp + 0x40;
    s6 = sp + 0x50;
    /* the asm leaves a1..a3 untouched here; Vec3_Set only reads its float args */
    Vec3_Set(s7, 0.0f, -0.5f, 0.5f);

    s1 = *(u8 **)arg0;
    if (s1 == NULL) {
        return;
    }
    do {
        if (F32(s1, 0x8) < F32(s1, 0xC)) {
            s0 = s1 + 0x40;
            s2 = s1 + 0x60;
            func_0012A360(F32(s1, 0x18), s0, s2, s0, arg3);
            Vec3_Add(s1 + 0x50, s0, arg1 + 0x10);
            Vec3_Add(s2, s2, s1 + 0x90);
            if (0.0f < F32(s1, 0x38)) {
                Mtx_RotateZ(F32(s1, 0x30), sp, arg0 + 0x80);
                func_00129C50(s6, sp, s7);
                func_00129C50(s6, s1 + 0xA0, s6);
                func_00129C50(s6, arg0 + 0xC0, s6);
                /* later call: a3 is no longer an argument (garbage after the callee) */
                ((void (*)(f32, void *, void *, void *))func_0012A360)(F32(s1, 0x38), s2, s6, s2);
                sum = F32(s1, 0x30) + F32(s1, 0x34);
                if (D_00385140 <= sum) {
                    F32(s1, 0x30) = sum - D_00385138;
                } else if (sum <= D_00385144) {
                    F32(s1, 0x30) = sum + D_00385138;
                }
            }
            Vec3_Normalize(s2, s2);

            v1 = S32(s1, 0);
            if (!(v1 & 2) && (F32(s3, 0x78) <= F32(s1, 0x8))) {
                S32(s1, 0x8C) = 0;
                v1 = v1 | 2;
                S32(s1, 0) = v1;
            }
            if (((v1 & 4) == 0) && (F32(s1, 0x14) <= F32(s1, 0x8))) {
                f20 = F32(s1, 0xC) - F32(s1, 0x8);
                v1 = v1 | 4;
                S32(s1, 0) = v1;
                F32(s1, 0x8C) = -F32(s1, 0x7C) / f20;
            }
            if ((v1 & 8) == 0) {
                if (F32(s1, 0x10) <= F32(s1, 0x8)) {
                    f20 = F32(s1, 0xC) - F32(s1, 0x8);
                    r = rand();
                    F32(s1, 0x1C) = ((F32(s3, 0x40) + F32(s3, 0x44) * ((f32)r / D_0038513C)) * F32(arg1, 0x4) - F32(s1, 0x18)) / f20;
                    r = rand();
                    F32(s1, 0x24) = ((F32(s3, 0x58) + F32(s3, 0x5C) * ((f32)r / D_0038513C)) * F32(arg1, 0x4) - F32(s1, 0x20)) / f20;
                    r = rand();
                    S32(s1, 0) = S32(s1, 0) | 8;
                    F32(s1, 0x2C) = ((F32(s3, 0x70) + F32(s3, 0x74) * ((f32)r / D_0038513C)) * F32(arg1, 0x4) - F32(s1, 0x28)) / f20;
                }
            }
            s0 = s1 + 0x70;
            func_00129B28(s0, s0, s1 + 0x80);
            func_00129D68(s0, s0, 0.0f, 255.0f);

            f0 = F32(s1, 0x20) + F32(s1, 0x24);
            f1 = F32(s1, 0x18) + F32(s1, 0x1C);
            F32(s1, 0x20) = f0;
            F32(s1, 0x18) = f1;
            if (f0 < 0.0f) {
                F32(s1, 0x20) = 0.0f;
            }
            f0 = F32(s1, 0x28) + F32(s1, 0x2C);
            F32(s1, 0x28) = f0;
            if (f0 < 0.0f) {
                F32(s1, 0x28) = 0.0f;
            }
            if (S32(s1, 0xE8) != 0) {
                func_001BD900(arg1, s1);
            }
            F32(s1, 0x8) = F32(s1, 0x8) + 1.0f;
            s0 = s1 + 0xE0;
        } else {
            if (S32(s1, 0xE8) != 0) {
                func_001BCD58(s1);
            }
            s0 = s1 + 0xE0;
            func_001BCDA0(arg0, s1);
            S32(s1, 0) = 0;
            S32(arg0, 0x68) = S32(arg0, 0x68) - 1;
        }
        s1 = *(u8 **)s0;
    } while (s1 != NULL);
}
