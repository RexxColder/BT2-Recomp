#include "common.h"

s32 BtlScene_IsEffectStopped(s32 arg0, s32 arg1);
void BtlTask_SetDead(void *arg0);
f32 EftMath_WrapAngle(f32 farg0);
void Mtx_StoreIdentity(void *arg0);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
f32 func_00129E08(void *arg0);
void func_001890C8(void *arg0);
void func_00189530(f32 farg0, f32 farg1, void *arg0, void *arg1);
void func_00189EE8(void *arg0, void *arg1, void *arg2);
void func_00189FD8(f32 farg0, f32 farg1, f32 farg2, void *arg0, void *arg1, void *arg2, void *arg3);
void func_0018A2C8(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, void *arg0, void *arg1, void *arg2);
void func_0018B880(f32 farg0, f32 farg1, void *arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_00188218(u8 *arg0) {
    u8 sp[0x40];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *head;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f8;
    f32 f12;
    f32 f20;
    f32 x;
    s32 t;
    f32 d;
    s32 a0;
    s32 v0;
    s32 v1;
    s32 fl;

    s1 = *(u8 **)(arg0 + 0x38);
    s3 = *(u8 **)(s1 + 0x30);
    memset(sp, 0, 0x40);
    if (BtlScene_IsEffectStopped(*(s32 *)(s1 + 0xD0), *(u8 *)(s1 + 0x1DC)) != 0) {
        return;
    }
    Mtx_StoreIdentity(sp);
    f1 = *(f32 *)(s1 + 0xC8);
    s4 = s1 + 0x70;
    if (0.0f < f1) {
        *(f32 *)(s1 + 0xC8) = f1 - 1.0f;
        return;
    }
    Vec3_Sub(s4, s1 + 0x60, s1 + 0x50);
    *(f32 *)(s1 + 0xC4) = func_00129E08(s4);
    Vec3_Normalize(s4, s4);

    f8 = *(f32 *)(s1 + 0x84);
    if (0.0f <= f8 && f8 < *(f32 *)(s3 + 0xA8) * 30.0f) {
        *(f32 *)(s1 + 0x88) = *(f32 *)(s1 + 0x88) + *(f32 *)(s1 + 0x8C);
        *(f32 *)(s1 + 0xAC) = *(f32 *)(s1 + 0xAC) + *(f32 *)(s1 + 0x98);
        *(f32 *)(s1 + 0xB0) = *(f32 *)(s1 + 0xB0) + *(f32 *)(s1 + 0xA4);
        *(f32 *)(s1 + 0xB4) = *(f32 *)(s1 + 0xB4) + *(f32 *)(s1 + 0xB8);
    }
    if (*(f32 *)(s3 + 0xA8) * 30.0f <= f8 && f8 < *(f32 *)(s3 + 0xAC) * 30.0f) {
        *(f32 *)(s1 + 0x88) = *(f32 *)(s1 + 0x88) + *(f32 *)(s1 + 0x90);
        *(f32 *)(s1 + 0xAC) = *(f32 *)(s1 + 0xAC) + *(f32 *)(s1 + 0x9C);
        *(f32 *)(s1 + 0xB0) = *(f32 *)(s1 + 0xB0) + *(f32 *)(s1 + 0xA8);
        *(f32 *)(s1 + 0xB4) = *(f32 *)(s1 + 0xB4) + *(f32 *)(s1 + 0xBC);
    }
    *(f32 *)(s1 + 0x94) = *(f32 *)(s1 + 0x94) + *(f32 *)(s1 + 0xAC);
    *(f32 *)(s1 + 0xA0) = *(f32 *)(s1 + 0xA0) + *(f32 *)(s1 + 0xB0);
    if (f8 < *(f32 *)(s3 + 0xAC) * 30.0f) {
        *(f32 *)(s1 + 0x84) = f8 + 1.0f;
    }

    v1 = *(s32 *)(s1 + 0x1D8);
    if ((v1 & 4) == 0) {
        func_001890C8(s1);
        head = *(u8 **)(s1 + 0x1E0);
    } else {
        f1 = *(f32 *)(s1 + 0xCC);
        if (0.0f < f1) {
            func_001890C8(s1);
            f1 = *(f32 *)(s1 + 0xCC);
        } else {
            *(s32 *)(s1 + 0x1D8) = v1 | 0x10;
        }
        *(f32 *)(s1 + 0xCC) = f1 - 1.0f;
        head = *(u8 **)(s1 + 0x1E0);
    }

    s0 = head;
    while (s0 != NULL) {
        f1 = *(f32 *)(s0 + 0xB4);
        if (0.0f <= f1) {
            *(f32 *)(s0 + 0xB4) = f1 - 1.0f;
        } else {
            fl = *(u16 *)(s0 + 0xBE);
            if ((fl & 2) == 0) {
                if ((*(s32 *)(s1 + 0x1D8) & 0x10) != 0) {
                    *(u16 *)(s0 + 0xBE) = 0;
                    func_00189EE8(s1 + 0x1E0, s1 + 0x1E4, s0);
                    fl = *(u16 *)(s0 + 0xBE);
                }
            }
            f20 = *(f32 *)(s0 + 0xB0) / *(f32 *)(s0 + 0xB8);
            if ((fl & 2) != 0) {
                if (f20 < *(f32 *)(s3 + 0x78)) {
                    fl = fl | 0x40;
                } else {
                    fl = fl & 0xFFBF;
                }
                *(u16 *)(s0 + 0xBE) = (u16)fl;
                if (*(f32 *)(s3 + 0x7C) <= f20 && f20 < 1.0f) {
                    fl = fl | 0x80;
                    *(u16 *)(s0 + 0xBE) = (u16)fl;
                }
                fl = *(u16 *)(s0 + 0xBE);
                if (*(f32 *)(s3 + 0x80) <= f20) {
                    fl = (fl & 0xFFFE) | 8;
                    *(u16 *)(s0 + 0xBE) = (u16)fl;
                }
            }
            if ((fl & 0x40) != 0) {
                *(f32 *)(s0 + 0x2C) = *(f32 *)(s0 + 0x2C) + *(f32 *)(s0 + 0x80);
            }
            if ((fl & 0x80) != 0) {
                *(f32 *)(s0 + 0x2C) = *(f32 *)(s0 + 0x2C) - *(f32 *)(s0 + 0x84);
            }
            s2 = s0 + 0x20;
            if ((fl & 0x100) == 0) {
                Vec3_Add(s2, s2, s0 + 0x30);
            }
            func_0018B880(0.0f, 255.0f, s2);
            fl = *(u16 *)(s0 + 0xBE);
            if ((fl & 1) != 0) {
                *(f32 *)(s0 + 0x88) = *(f32 *)(s0 + 0x88) + *(f32 *)(s0 + 0x90);
                *(f32 *)(s0 + 0x8C) = *(f32 *)(s0 + 0x8C) + *(f32 *)(s0 + 0x98);
            }
            if ((fl & 8) != 0) {
                *(f32 *)(s0 + 0x88) = *(f32 *)(s0 + 0x88) + *(f32 *)(s0 + 0x94);
                *(f32 *)(s0 + 0x8C) = *(f32 *)(s0 + 0x8C) + *(f32 *)(s0 + 0x9C);
            }
            f12 = *(f32 *)(s0 + 0xA4) + *(f32 *)(s0 + 0xA8);
            *(f32 *)(s0 + 0xA4) = EftMath_WrapAngle(f12);

            v1 = *(s32 *)(s3 + 0xA4);
            if ((v1 & 2) != 0) {
                if ((v1 & 8) != 0) {
                    func_0018A2C8(*(f32 *)(s1 + 0x88) * *(f32 *)(s1 + 0x80), *(f32 *)(s1 + 0x94),
                                  *(f32 *)(s1 + 0xA0), *(f32 *)(s3 + 0x34), *(f32 *)(s3 + 0x38),
                                  s0, sp, s1 + 0x40);
                }
                v1 = *(s32 *)(s3 + 0xA4);
            }
            if ((v1 & 4) != 0) {
                func_00189530(*(f32 *)(s1 + 0xAC), *(f32 *)(s1 + 0xB0), s0, sp);
                v1 = *(s32 *)(s3 + 0xA4);
            }
            if ((v1 & 1) != 0 && (v1 & 0x20) != 0) {
                func_00189FD8(*(f32 *)(s1 + 0x88) * *(f32 *)(s1 + 0x80), *(f32 *)(s3 + 0x34),
                              *(f32 *)(s3 + 0x38), s0, sp, s4, s1 + 0x40);
            }

            f2 = *(f32 *)(s0 + 0xB0);
            x = f2;
            t = (s32)x;
            d = x - (f32)t;
            if (d > 0.5f || (d == 0.5f && (t & 1) != 0)) {
                t = t + 1;
            } else if (d < -0.5f || (d == -0.5f && (t & 1) != 0)) {
                t = t - 1;
            }
            a0 = t;
            v0 = *(u8 *)(s3 + 0xA2);
            if (v0 != 0 && (a0 % v0) == 0) {
                *(u8 *)(s0 + 0xBD) = (u8)(*(u8 *)(s0 + 0xBD) + 1);
            }
            if (!(*(u8 *)(s0 + 0xBD) < *(u8 *)(s1 + 0x1D5))) {
                *(u8 *)(s0 + 0xBD) = 0;
            }
            f0 = f2 + 1.0f;
            *(f32 *)(s0 + 0xB0) = f0;
            if (*(f32 *)(s0 + 0xB8) <= f0) {
                fl = *(u16 *)(s0 + 0xBE);
                if ((fl & 2) != 0) {
                    *(u16 *)(s0 + 0xBE) = (u16)(fl & 0xFFFD);
                }
            }
        }
        s0 = *(u8 **)(s0 + 0xC0);
    }

    a0 = *(s32 *)(s1 + 0x1D8);
    v0 = a0 & 0x20;
    if ((a0 & 4) == 0) {
        f1 = *(f32 *)(s1 + 0xC0);
        if (0.0f < f1) {
            f0 = f1 - 1.0f;
            *(f32 *)(s1 + 0xC0) = f0;
            if (f0 <= 0.0f) {
                *(f32 *)(s1 + 0xC0) = 0.0f;
                a0 = a0 | 4;
                *(s32 *)(s1 + 0x1D8) = a0;
                v0 = a0 & 0x20;
            }
        }
    }

    head = *(u8 **)(s1 + 0x1E0);
    if (v0 != 0 && head != NULL) {
        s0 = head;
        *(u16 *)(s0 + 0xBE) = 0;
        do {
            func_00189EE8(s1 + 0x1E0, s1 + 0x1E4, s0);
            s0 = *(u8 **)(s0 + 0xC0);
            if (s0 != NULL) {
                *(u16 *)(s0 + 0xBE) = 0;
            }
        } while (s0 != NULL);
    }

    head = *(u8 **)(s1 + 0x1E0);
    if (head == NULL) {
        if ((*(s32 *)(s1 + 0x1D8) & 0x10) != 0) {
            *(s32 *)(s1 + 0x1D8) = 0;
            BtlTask_SetDead(arg0);
        }
    }
}
