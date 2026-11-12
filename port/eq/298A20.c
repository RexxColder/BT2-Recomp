#include "common.h"

extern u8 D_0038B058[];
extern u8 D_00377718[];
extern u8 D_00377728[];
extern f32 D_0038720C;
void func_0026E9E8(s32 arg0);
void func_0026EBC0(s32 arg0, u8 *arg1, u8 *arg2);
void func_0026F0E8(s32 arg0, u8 *arg1, u8 *arg2);
s32 rand(void);

#define B D_0038B058
#define U16(p) (*(u16 *)(p))
#define S32(p) (*(s32 *)(p))
#define F32(p) (*(f32 *)(p))

/* 0x00298A20: per-frame update of two cursors (entries at +0x50, stride 0x1C) and seven
 * 6-byte slot entries (+0x24) tied to the 0x38-byte objects at *(B+0x20). */
void func_00298A20(void) {
    u8 sp[0x10];
    s32 i, a1, idx, cnt;
    u8 *e, *obj, *ent, *a2, *q, *p;
    s32 s5, s2, s6, s7;
    f32 f0, f1;

    func_0026E9E8(S32(B + 8));
    if ((B[0] & 2) == 0) {
        for (i = 0; i < 2; i++) {
            u8 *E = B + 0x50 + 0x1C * i;
            f32 *px = (f32 *)(B + 0x5C + 0x1C * i);
            f32 *py = (f32 *)(B + 0x60 + 0x1C * i);
            obj = (u8 *)S32(B + 0x20) + 0x38 * i + 0x230;
            if (U16(E) & 1) {
                s32 v;
                *px = *px + F32(B + 0x64 + 0x1C * i);
                *py = *py + F32(B + 0x68 + 0x1C * i);
                v = (s32)*px;
                S32(obj + 4) = v;
                S32(obj + 0xC) = v + 0x40;
                v = (s32)*py;
                S32(obj + 8) = v;
                S32(obj + 0x10) = v + 0x40;
                if (U16(E) & 2) {
                    f32 *c = (f32 *)(B + 0x58 + 0x1C * i);
                    f0 = *c - 1.0f;
                    *c = f0;
                    if (f0 < 0.0f) {
                        U16(E) = 0;
                        S32(c) = 0;
                        *px = 225.0f;
                        *py = 192.0f;
                        S32(obj + 0x10) = 0x100;
                        S32(obj + 4) = 0xE1;
                        S32(obj + 0xC) = 0x121;
                        S32(obj + 8) = 0xC0;
                    }
                }
            } else {
                *px = 225.0f;
                *py = 192.0f;
                S32(obj + 0x10) = 0x100;
                S32(obj + 4) = 0xE1;
                S32(obj + 0xC) = 0x121;
                S32(obj + 8) = 0xC0;
            }
            U16(E + 2) = U16(E + 2) ^ 1;
        }
    } else {
        a1 = 0;
        s2 = 1;
        do {
            q = (u8 *)S32(B + 0x20) + a1 + 0x230;
            S32(q + 0x34) = S32(q + 0x34) - 8;
            q = (u8 *)S32(B + 0x20) + a1 + 0x230;
            if (S32(q + 0x34) < 0) {
                S32(q + 0x34) = 0;
            }
            a1 += 0x38;
            s2--;
        } while (s2 >= 0);
    }

    if ((B[0] & 2) != 0) {
        goto part3;
    }
    while (S32(B + 0x88) < 4) {
        idx = rand() % 7;
        p = B + 0x24 + 6 * idx;
        if ((U16(p) & 1) == 0) {
            U16(p) = 1;
            U16(B + 0x26 + 6 * idx) = (u16)(rand() % 15 + 0x1E);
            S32(B + 0x88) = S32(B + 0x88) + 1;
            S32((u8 *)S32(B + 0x20) + 56 * idx + 0xA4) = 0x80;
        }
    }
    if ((B[0] & 2) != 0) {
        goto part3;
    }

    s2 = 1;
    s5 = 0;
    s6 = 0x80;
    s7 = 0x80;
    e = B + 0x50;
    do {
        u8 *s3 = e + (0x64 - 0x50);
        u8 *s4 = e + (0x68 - 0x50);
        s32 t1 = s5 << 3;
        u16 a0 = U16(e);
        a2 = (u8 *)S32(B + 0x20) + t1 + 0x230;
        if ((a0 & 1) != 0) {
            if ((a0 & 4) != 0) {
                if (S32(a2 + 0x10) >= 0x161) {
                    f1 = (f32)S32(a2 + 4);
                    F32(e + 0x14) = 225.0f - f1;
                    f1 = (225.0f - f1) / 10.0f;
                    f0 = (f32)S32((u8 *)S32(B + 0x20) + t1 + 0x238);
                    F32(e + 8) = 10.0f;
                    F32(e + 0x14) = f1;
                    F32(e + 0x18) = (192.0f - f0) / 10.0f;
                    F32(B + 0x90) = 4.0f;
                    F32(B + 0x8C) = 4.0f;
                    U16(e) = U16(e) | 2;
                    B[0] = B[0] | 4;
                    func_0026EBC0(S32(B + 8), D_00377718, sp);
                    func_0026F0E8(S32(B + 8), sp, D_00377728);
                }
            } else if ((a0 & 2) == 0) {
                s32 a3 = *(s16 *)(e + 4);
                s32 a1v = S32(a2 + 8);
                s32 a2v = S32(a2 + 4);
                s32 dx, dy;
                q = (u8 *)S32(B + 0x20) + 56 * a3 + 0x70;
                dy = a1v - S32(q + 8);
                dx = a2v - S32(q + 4);
                if (dx * dx + dy * dy < 0x800) {
                    u16 *a0p;
                    u16 v1;
                    f0 = (f32)a2v;
                    F32(e + 0x14) = 225.0f - f0;
                    f0 = (f32)S32((u8 *)S32(B + 0x20) + t1 + 0x238);
                    F32(e + 0x18) = 192.0f - f0;
                    a0p = (u16 *)(B + 0x24 + 6 * a3);
                    v1 = *a0p;
                    if ((v1 & 1) != 0 && (v1 & 2) == 0) {
                        f32 *vp = (f32 *)(B + 0xC + s6);
                        *a0p = v1 | 2;
                        f0 = *vp + D_0038720C;
                        *vp = f0;
                        if (10.0f < f0) {
                            *vp = 10.0f;
                        }
                        f0 = *vp;
                        f1 = F32(s3);
                        f0 = 30.0f / f0;
                        F32(s3) = f1 / f0;
                        f0 = *vp;
                        f1 = F32(s4);
                        f0 = 30.0f / f0;
                        F32(s4) = f1 / f0;
                        f0 = *vp;
                        F32(e + 8) = 30.0f / f0;
                    } else {
                        f1 = F32(e + 0x14);
                        f0 = F32(e + 0x18);
                        F32(e + 8) = 10.0f;
                        F32(e + 0x14) = f1 / 10.0f;
                        F32(e + 0x18) = f0 / 10.0f;
                        F32(B + 0xC + s7) = 6.0f;
                    }
                    U16(e) = U16(e) | 2;
                }
            }
        }
        s2--;
        e += 0x1C;
        s7 += 4;
        s6 += 4;
        s5 += 7;
    } while (s2 >= 0);

part3:
    {
        u8 *t0p = B + 0x28;
        s32 a3 = 0;
        u8 *a1p = B + 0x24;
        s32 n = 6;
        do {
            u16 a0 = U16(a1p);
            if ((a0 & 1) != 0) {
                u16 v0;
                s32 dec = 0;
                if ((a0 & 2) != 0 || (a0 & 4) != 0) {
                    dec = 1;
                } else {
                    v0 = U16(a1p + 2) - 1;
                    U16(a1p + 2) = v0;
                    if ((s16)v0 == -1) {
                        U16(a1p) = a0 | 4;
                    }
                }
                if (dec) {
                    q = (u8 *)S32(B + 0x20) + a3 + 0x70;
                    S32(q + 0x34) = S32(q + 0x34) - 8;
                    q = (u8 *)S32(B + 0x20) + a3 + 0x70;
                    if (S32(q + 0x34) < 0) {
                        S32(q + 0x34) = 0;
                        U16(a1p) = 0;
                        S32(B + 0x88) = S32(B + 0x88) - 1;
                    }
                }
                if ((U16(a1p) & 2) != 0) {
                    U16(t0p) = 1;
                } else {
                    U16(t0p) = 0;
                }
            }
            n--;
            t0p += 6;
            a3 += 0x38;
            a1p += 6;
        } while (n >= 0);
    }
}
