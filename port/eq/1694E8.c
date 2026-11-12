#include "common.h"

extern f32 D_0038482C;
extern f32 D_00384830;
extern f32 D_00384834;
extern f32 D_00384838;

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void Mtx_StoreIdentity(s32 arg0);
void Mtx_Translate(s32 arg0, s32 arg1, s32 arg2);
void Mtx_RotateXYZ(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void func_00128C58(f32 farg0, s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);
void func_00168FB8(s32 arg0, s32 arg1, s32 arg2);
void func_001693D8(s32 arg0, s32 arg1, s32 arg2);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_001EDD40(s32 arg0, s32 arg1);
f32 sinf(f32 farg0);

#define S32F(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F32F(p, off) (*(f32 *)((u8 *)(p) + (off)))

void func_001694E8(s32 arg0) {
    f32 fr[12];
    u8 *s7;
    u8 *s4;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    f32 *s6;
    f32 *fp;
    f32 *p;
    s32 s5;
    s32 v1;
    s32 a0v;
    f32 f0;
    f32 f2;
    f32 f20;
    f32 f21;
    f32 f22;

    s7 = (u8 *)arg0;
    s4 = (u8 *)S32F(s7, 0x38);
    s0 = (u8 *)S32F(s4, 0xB0);
    if (EftShot_TestBits(S32F(s0, 0), 2) != 0) {
        S32F(s4, 4) = S32F(s4, 4) | 9;
    } else if (EftShot_TestBits(S32F(s0, 0), 4) != 0) {
        S32F(s4, 4) = S32F(s4, 4) | 2;
    }
    if (S32F(s4, 0) & 5) {
        S32F(s4, 4) = S32F(s4, 4) & ~8;
    }

    s5 = 0;
    if (S32F(s4, 4) & 1) {
        f22 = 0.0f;
        f21 = 1.0f;
        fp = &fr[8];
        s1 = s4 + 0xAB0;
        do {
            v1 = S32F(s1, 0x34);
            if (!(v1 & 1)) {
                func_00168FB8((s32)s7, (s32)s1, s5);
                v1 = S32F(s1, 0x34) | 1;
                S32F(s1, 0x34) = v1;
            }
            a0v = S32F(s4, 4);
            if (a0v & 8) {
                if (!(v1 & 2)) {
                    f0 = F32F(s1, 0x38);
                    if (f0 <= 0.0f) {
                        func_001EDBD8(S32F(s1, 0x30), 1);
                        v1 = S32F(s1, 0x34) | 2;
                        S32F(s1, 0x34) = v1;
                    } else {
                        F32F(s1, 0x38) = f0 - f21;
                    }
                    if (!(v1 & 2)) {
                        goto next;
                    }
                    a0v = S32F(s4, 4);
                }
            } else {
                if (!(v1 & 2)) {
                    goto next;
                }
                func_001EDBD8(S32F(s1, 0x30), 0);
                v1 = S32F(s1, 0x34) & ~2;
                S32F(s1, 0x34) = v1;
                goto next;
            }

            /* L670: a0v holds the current word at s4+4 */
            if (!(a0v & 2)) {
                s3 = s1 + 0x60;
                F32F(s1, 0x74) = F32F(s1, 0x74) - F32F(s1, 0x50);
                s6 = &fr[4];
            } else {
                f0 = F32F(s1, 0x3C);
                if (!(f0 <= 0.0f)) {
                    s3 = s1 + 0x60;
                    F32F(s1, 0x3C) = f0 - f21;
                    s6 = &fr[4];
                } else {
                    if (!(v1 & 4)) {
                        func_001693D8((s32)s7, (s32)s1, s5);
                        S32F(s1, 0x34) = S32F(s1, 0x34) | 4;
                    }
                    s3 = s1 + 0x60;
                    func_00129BD0((s32)fp, (s32)(s4 + 0xA0), F32F(s1, 0x54));
                    Vec3_Add((s32)s3, (s32)s3, (s32)fp);
                    s6 = &fr[4];
                }
            }

            s0 = s1 + 0x70;
            func_00129C28((s32)s6, (s32)s0);
            f20 = D_0038482C;
            fr[5] = fr[5] + sinf(F32F(s1, 0x48)) * F32F(s1, 0x44);
            f2 = F32F(s1, 0x48) + F32F(s1, 0x4C);
            F32F(s1, 0x48) = f2;
            if (f20 < f2) {
                F32F(s1, 0x48) = f2 - D_00384830;
            }

            s2 = s1 + 0x90;
            Vec3_Add((s32)s0, (s32)s0, (s32)(s1 + 0x80));
            Vec3_Add((s32)s2, (s32)s2, (s32)(s1 + 0xA0));

            p = (f32 *)s2;
            v1 = 2;
            do {
                f0 = *p;
                if (f20 < f0) {
                    f0 = f0 - D_00384834;
                    *p = f0;
                } else if (f0 < D_00384838) {
                    f0 = f0 + D_00384834;
                    *p = f0;
                }
                v1 = v1 - 1;
                p += 1;
            } while (v1 >= 0);

            s0 = s1 + 0xB0;
            Mtx_StoreIdentity((s32)s0);
            func_00128C58(F32F(s1, 0x40), (s32)s0, (s32)s0);
            Mtx_RotateXYZ((s32)s0, (s32)s0, (s32)s2);
            Vec3_Add((s32)fr, (s32)s3, (s32)s6);
            fr[3] = f21;
            Mtx_Translate((s32)s0, (s32)s0, (s32)fr);
            func_001EDD40(S32F(s1, 0x30), (s32)s0);

next:
            s5 += 1;
            s1 += 0xF0;
        } while (s5 < 7);
    }
}
