#include "common.h"
void bt2_fightlog_note(const char *fmt, ...);

#define FLD(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define WLD(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define BLD(p, o) (*(u8 *)((u8 *)(p) + (o)))

extern f32 D_003850EC;
extern f32 D_003850F0;
extern f32 D_003850F4;
extern f32 D_003850F8;
extern f32 D_003850FC;

void Vec3_Set(void *dst, f32 x, f32 y, f32 z);
void Vec3_Add(void *dst, void *a, void *b);
void Vec3_Normalize(void *dst, void *src);
void func_0012A360(void *a0, void *a1, void *a2, f32 f12);
void func_00129C28(void *a0, void *a1);
void func_001B8B78(void *a0, void *a1);
void func_00129B28(void *a0, void *a1, void *a2);
void func_00129D68(void *a0, void *a1, f32 f12, f32 f13);
s32 rand(void);

void func_001BA518(u8 *arg0, u8 *arg1) {
    u8 tmp[16] __attribute__((aligned(16)));
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s5;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f0;
    f32 f1;
    f32 f5;
    f32 f6;
    f32 t;
    f32 scale;
    s32 fl;
    s32 r;

    s5 = *(u8 **)(arg1 + 0x38);
    Vec3_Set(tmp, 0.0f, -0.5f, 0.5f);
    s1 = *(u8 **)arg0;
    if (s1 == NULL) {
        return;
    }
    f21 = D_003850EC;
    f22 = 1.0f;

    do {
        if (FLD(s1, 0x8) < FLD(s1, 0xC)) {
            /* live particle */
            s2 = s1 + 0x50;
            s3 = s1 + 0x90;
            func_0012A360(s2, s3, s2, FLD(s1, 0x24));
            if (!(WLD(s1, 0) & 0x40)) {
                s0 = s1 + 0x70;
                Vec3_Add(s0, s2, s1 + 0x60);
                Vec3_Add(s1 + 0x80, s0, arg1 + 0x10);
            } else {
                Vec3_Add(s1 + 0x80, s2, s1 + 0x60);
                s0 = s1 + 0x70;
                Vec3_Add(s1 + 0x80, s1 + 0x80, s0);
            }
            Vec3_Add(s3, s3, s1 + 0xC0);
            Vec3_Normalize(s3, s3);

            fl = WLD(s1, 0);
            if ((WLD(arg0, 0x60) & 0x80) && !(fl & 0x40)) {
                func_00129C28(s1 + 0x70, arg1 + 0x10);
                fl |= 0x40;
                WLD(s1, 0) = fl;
            }

            if (!(fl & 2)) {
                if (FLD(s5, 0xC8) <= FLD(s1, 0x8)) {
                    WLD(s1, 0xBC) = 0;
                    fl |= 2;
                    WLD(s1, 0) = fl;
                }
            }

            if (!(fl & 4)) {
                if (FLD(s1, 0x14) <= FLD(s1, 0x8)) {
                    fl |= 4;
                    WLD(s1, 0) = fl;
                    f20 = FLD(s1, 0xC) - FLD(s1, 0x8);
                    FLD(s1, 0xBC) = -FLD(s1, 0xAC) / f20;
                }
            }

            if (!(fl & 8)) {
                if (FLD(s1, 0x10) <= FLD(s1, 0x8)) {
                    f20 = FLD(s1, 0xC) - FLD(s1, 0x8);
                    r = rand();
                    FLD(s1, 0x28) = ((FLD(arg0, 0xBC) + FLD(arg0, 0xC0) * ((f32)r / f21)) * FLD(arg1, 0x4) - FLD(s1, 0x24)) / f20;
                    r = rand();
                    FLD(s1, 0x30) = ((FLD(arg0, 0xEC) + FLD(arg0, 0xF0) * ((f32)r / f21)) * FLD(arg1, 0x4) - FLD(s1, 0x2C)) / f20;
                    r = rand();
                    FLD(s1, 0x38) = ((FLD(arg0, 0x11C) + FLD(arg0, 0x120) * ((f32)r / f21)) * FLD(arg1, 0x4) - FLD(s1, 0x34)) / f20;
                    r = rand();
                    f0 = FLD(s5, 0x13C) + FLD(s5, 0x140) * ((f32)r / f21);
                    FLD(s1, 0x48) = f0;
                    fl = WLD(s1, 0);
                    if (fl & 0x20) {
                        FLD(s1, 0x48) = -f0;
                    }
                    fl |= 8;
                    WLD(s1, 0) = fl;
                }
            }

            s0 = s1 + 0xA0;
            func_00129B28(s0, s0, s1 + 0xB0);
            f20 = 0.0f;
            func_00129D68(s0, s0, 0.0f, 255.0f);
            { static int n; if ((n++ % 2000) == 0) bt2_fightlog_note("PTCL-COLOR rgba %g %g %g %g delta %g %g %g %g t %g fin %g fade %g fl %x", /* TEMP */
                FLD(s1, 0xA0), FLD(s1, 0xA4), FLD(s1, 0xA8), FLD(s1, 0xAC), FLD(s1, 0xB0), FLD(s1, 0xB4), FLD(s1, 0xB8), FLD(s1, 0xBC),
                FLD(s1, 0x8), FLD(s1, 0xC), FLD(s1, 0x14), WLD(s1, 0)); }

            f0 = FLD(s1, 0x2C) + FLD(s1, 0x30);
            f1 = FLD(s1, 0x24) + FLD(s1, 0x28);
            FLD(s1, 0x2C) = f0;
            FLD(s1, 0x24) = f1;
            if (f0 < f20) {
                FLD(s1, 0x2C) = f20;
            }

            f1 = FLD(s1, 0x34) + FLD(s1, 0x38);
            FLD(s1, 0x34) = f1;
            if (f1 < f20) {
                FLD(s1, 0x34) = f20;
            }

            f1 = FLD(s1, 0x44) + FLD(s1, 0x48);
            FLD(s1, 0x44) = f1;
            if (D_003850F0 < f1) {
                FLD(s1, 0x44) = f1 - D_003850F4;
            } else if (f1 < D_003850F8) {
                FLD(s1, 0x44) = f1 + D_003850FC;
            }

            f5 = FLD(s1, 0x18);
            f6 = FLD(s1, 0x1C);
            t = f5 / f6;
            scale = FLD(s5, 0xBC) + FLD(s1, 0x20) * t;
            FLD(s1, 0x40) = FLD(s1, 0x34) * scale;
            FLD(s1, 0x3C) = FLD(s1, 0x2C) * scale;

            fl = WLD(s1, 0);
            if (!(fl & 0x10)) {
                f0 = f5 + f22;
                FLD(s1, 0x18) = f0;
                if (f6 <= f0) {
                    FLD(s1, 0x18) = f6;
                    fl |= 0x10;
                    WLD(s1, 0) = fl;
                }
            } else {
                f0 = f5 - f22;
                FLD(s1, 0x18) = f0;
                if (f0 <= 0.0f) {
                    FLD(s1, 0x18) = 0.0f;
                    fl &= ~0x10;
                    WLD(s1, 0) = fl;
                }
            }

            if (WLD(arg0, 0x60) & 0x40) {
                s32 aa = BLD(s1, 0x4);
                s32 vv = *(s16 *)(s5 + 0x15C);
                f0 = (f32)(aa % vv) * FLD(arg0, 0x70);
                FLD(s1, 0xD0) = f0;
                FLD(s1, 0xD4) = f0 + FLD(arg0, 0x70);
                f0 = (f32)(aa / vv) * FLD(arg0, 0x74);
                FLD(s1, 0xD8) = f0;
                FLD(s1, 0xDC) = f0 + FLD(arg0, 0x74);

                r = rand();
                FLD(s1, 0x4C) = FLD(s1, 0x4C) + (f32)r / f21;
                if (FLD(s5, 0x160) <= FLD(s1, 0x4C)) {
                    FLD(s1, 0x4C) = FLD(s1, 0x4C) - FLD(s5, 0x160);
                    {
                        u8 nb = (u8)(BLD(s1, 0x4) + 1);
                        BLD(s1, 0x4) = nb;
                        if ((s32)nb >= WLD(arg0, 0x6C)) {
                            BLD(s1, 0x4) = 0;
                        }
                    }
                }
            }

            FLD(s1, 0x8) = FLD(s1, 0x8) + f22;
        } else {
            func_001B8B78(arg0, s1);
            WLD(s1, 0) = 0;
            WLD(arg0, 0x68) = WLD(arg0, 0x68) - 1;
        }
        s1 = *(u8 **)(s1 + 0x120);
    } while (s1 != NULL);
}
