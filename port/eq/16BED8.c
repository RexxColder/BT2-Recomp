#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define S32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define S64(p, off) (*(s64 *)((u8 *)(p) + (off)))

extern f32 D_00384874;
extern f32 D_00384878;
extern f32 D_0038487C;

u8 *func_0020B3D0(u8 *a0);
s32 EftShot_TestBits(u8 *a0, s32 a1);
void EftGlow_Request(u8 *a0, s32 a1);
void func_0016CAE0(u8 *a0, s32 a1);
void func_002822C8(f32 f12, s32 a0, s32 a1);
void func_00208DE8(u8 *a0, u8 *a1, s32 a2);
void func_00208F18(u8 *a0, u8 *a1, s32 a2);
void Vec4_Set(void *a0, f32 f12, f32 f13, f32 f14, f32 f15);
void Vec3_Normalize(void *a0, void *a1);
void Vec3_Sub(void *a0, void *a1, void *a2);
void func_00129BD0(void *a0, void *a1, f32 f12);
void func_001DDBE0(void *a0, s64 a1, s64 a2, s64 a3, s64 t0, s64 t1);

void func_0016BED8(u8 *arg0) {
    s64 frame[0x24];
    u8 *sp;
    u8 *P;
    u8 *Q;
    u8 *R;
    u8 *temp;
    u8 *q0;
    u8 *s0;
    u8 *s1;
    s32 T;

    sp = (u8 *)frame;
    P = *(u8 **)(arg0 + 0x38);
    Q = *(u8 **)(P + 0xB0);
    q0 = *(u8 **)Q;
    temp = func_0020B3D0(q0);
    R = *(u8 **)(Q + 0x20);
    T = *(s32 *)R;

    if (T == 0x134) {
        /* X block */
        if (EftShot_TestBits(q0, 2) != 0) {
            S32(P, 0) = S32(P, 0) | 0x400;
        }
        if ((S32(P, 0) & 0x400) != 0) {
            s0 = P + 0x30;
            func_00208DE8(q0, s0, 0x2E);
            func_00208DE8(q0, sp, 3);
            Vec3_Sub(s0, sp, s0);
            F32(P, 0x3C) = 1.0f;
            Vec3_Normalize(s0, s0);
        }
    } else if (T < 0x135) {
        if (T == 0x116) {
            if (EftShot_TestBits(temp, 0x10) != 0) {
                func_002822C8(D_00384874, 0, 0);
            }
            if (EftShot_TestBits(temp, 0x20) != 0) {
                func_002822C8(D_00384878, 0, 1);
            }
        } else if (T >= 0x117) {
            if (T == 0x124) {
                if (EftShot_TestBits(q0, 4) != 0) {
                    EftGlow_Request(q0, 0);
                }
                if (EftShot_TestBits(temp, 4) != 0) {
                    EftGlow_Request(q0, 1);
                }
            } else if (T == 0x133) {
                /* C060 block, a1 = 4 */
                if (EftShot_TestBits(q0, 4) != 0) {
                    S32(P, 0) = S32(P, 0) | 0x400;
                }
                if ((S32(P, 0) & 0x400) != 0) {
                    func_0016CAE0(arg0, 1);
                }
            }
        } else if (T == 0x9A) {
            if (EftShot_TestBits(q0, 0x10) != 0) {
                EftGlow_Request(q0, 0);
            }
            if (EftShot_TestBits(q0, 0x20) != 0) {
                EftGlow_Request(q0, 1);
            }
        }
    } else {
        if (T == 0x15C) {
            S32(P, 0) = S32(P, 0) | 0x8000;
            /* C064 block, a1 = 0x10 */
            if (EftShot_TestBits(q0, 0x10) != 0) {
                S32(P, 0) = S32(P, 0) | 0x400;
            }
            if ((S32(P, 0) & 0x400) != 0) {
                func_0016CAE0(arg0, 1);
            }
        } else if (T == 0x162 || T == 0x163) {
            /* C138 block */
            if (EftShot_TestBits(q0, 4) != 0) {
                S32(P, 0) = S32(P, 0) | 0x800;
            }
            s1 = P + 0x80;
            if ((S32(P, 0) & 0x800) != 0) {
                s0 = func_0020B3D0(q0);
                func_00208DE8(s0, s1, 3);
            } else {
                func_00208DE8(q0, s1, 0x11);
            }
        }
    }

    /* tail (C18C / C190 / C194) */
    if (T == 0x9C || T == 0x9D || T == 0x163) {
        if (EftShot_TestBits(q0, 0x20) == 0) {
            return;
        }
        /* vector path (C1B8) */
        func_00208F18(q0, sp + 0x20, 0x36);
        s0 = sp + 0x10;
        Vec4_Set(s0, -F32(sp, 0x40), -F32(sp, 0x44), -F32(sp, 0x48), 1.0f);
        Vec3_Normalize(s0, s0);
        Vec4_Set(sp, F32(sp, 0x50), F32(sp, 0x54), F32(sp, 0x58), 1.0f);
        s1 = sp + 0x60;
        func_00129BD0(s1, s0, D_0038487C);
        Vec3_Sub(sp, sp, s1);

        S32(sp, 0xB0) = *(s32 *)Q;
        S32(sp, 0xB4) = *(s32 *)(R + 0xC);
        F32(sp, 0xB8) = 0.25f;
        F32(sp, 0xBC) = 1.0f;
        F32(sp, 0xC0) = 64.0f;
        F32(sp, 0xC4) = 1.0f;
        {
            s64 t2 = S64(sp, 0x0);
            s64 a3 = S64(sp, 0x8);
            s64 t0 = S64(sp, 0x10);
            s64 t1 = S64(sp, 0x18);
            s64 v0v = S64(sp, 0xB0);
            s64 v1v = S64(sp, 0xB8);
            s64 a1v = S64(sp, 0xC0);
            s64 a2v = S64(sp, 0xC8);
            S64(sp, 0x70) = v0v;
            S64(sp, 0x78) = v1v;
            S64(sp, 0x80) = a1v;
            S64(sp, 0x88) = a2v;
            S64(sp, 0x90) = t2;
            S64(sp, 0x98) = a3;
            S64(sp, 0xA0) = t0;
            S64(sp, 0xA8) = t1;
            S64(sp, 0xD0) = t2;
            S64(sp, 0xD8) = a3;
            S64(sp, 0xE0) = t0;
            S64(sp, 0xE8) = t1;
            func_001DDBE0(sp + 0x70, a1v, a2v, a3, t0, t1);
        }
    }
}
