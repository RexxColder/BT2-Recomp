#include "common.h"

#define F32AT(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define S32AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U16AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define PTRAT(p, o) (*(u8 **)((u8 *)(p) + (o)))
/* cvt.w.s: truncates toward zero, written out */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(out, x) do { \
    (out) = (s32)(x); \
} while (0)

void func_0025EFD0(void *arg0);
u8 *func_00269A40(void *, s32);
void BtlObjAnim_SampleRot(f32, void *, void *, void *);
void BtlObjAnim_SamplePosRot(f32, void *, void *, void *, void *);
void func_003126C8(void *, void *);
void sceVu0InterVector(f32, void *, void *, void *);
void Quat_Slerp(f32, void *, void *, void *);

void func_0025F2A0(void *arg0) {
    u8 sp[0x20];
    u8 *st;
    u8 *s4;
    u8 *s0;
    u8 *s3;
    u8 *a0p;
    u8 *ta;
    s32 s1;
    s32 a1v;
    s32 v0;
    u16 s5;
    u16 v1;
    f32 f20;
    f32 f21;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;

    st = (u8 *)arg0 + 0xBD0;
    if (S32AT(st, 0x28) == 0) {
        func_0025EFD0(arg0);
        return;
    }
    f20 = 1.0f;
    f21 = 0.0f;
    s4 = PTRAT(arg0, 0x48);

    for (;;) {
        s5 = U16AT(s4, 0xA);
        s0 = func_00269A40(arg0, s5);
        S32AT(s0, 0xD0) = S32AT(s0, 0xD0) & ~1;

        if ((u32)s5 < 0x47) {
            s1 = s5 * 2;
            a0p = PTRAT(st, 0x28);
            v1 = U16AT(a0p, 6 + s1);
            if (v1 != 0) {
                ta = a0p + (v1 << 2);
                if (U16AT(ta, 0) & 1) {
                    /* bit set: rotation sample, then the position from the second table */
                    BtlObjAnim_SampleRot(F32AT(st, 0x10), ta, s0 + 0x90, st + s1 + 0x30);
                    func_003126C8(s0 + 0x80, s4 + 0x30);
                } else {
                    s3 = s0 + 0x80;
                    BtlObjAnim_SamplePosRot(F32AT(st, 0x10), ta, s3, s0 + 0x90, st + s1 + 0x30);
                }
            } else {
                func_003126C8(s0 + 0x80, s4 + 0x30);
                S32AT(s0, 0x90) = 0;
                S32AT(s0, 0x94) = 0;
                S32AT(s0, 0x98) = 0;
                F32AT(s0, 0x9C) = f20;
            }
            s3 = s0 + 0x80;

            /* L25F3E4 */
            a0p = PTRAT(st, 0x2C);
            if (a0p != 0 && f21 < F32AT(st, 0x24)) {
                f3 = F32AT(st, 0x8);
                f2 = F32AT(st, 0xC);
                f0 = F32AT(st, 0x10);
                CVT_W_S(a1v, f0);
                if (f3 != f2) {
                    f0 = f2 / f3;
                    f1 = (f32)a1v * f0;
                    CVT_W_S(a1v, f1);
                    if (f2 < (f32)a1v) {
                        CVT_W_S(a1v, f2);
                    }
                }
                v1 = U16AT(a0p, 6 + s1);
                if (v1 != 0) {
                    ta = a0p + (v1 << 2);
                    if (U16AT(ta, 0) & 1) {
                        BtlObjAnim_SampleRot((f32)a1v, ta, sp, st + s1 + 0xBE);
                        func_003126C8(sp + 0x10, s4 + 0x30);
                    } else {
                        BtlObjAnim_SamplePosRot((f32)a1v, ta, sp + 0x10, sp, st + s1 + 0xBE);
                    }
                    sceVu0InterVector(F32AT(st, 0x24), s3, sp + 0x10, s3);
                    F32AT(s0, 0x8C) = f20;
                    Quat_Slerp(F32AT(st, 0x24), s0 + 0x90, s0 + 0x90, sp);
                }
            }

            /* L25F504 */
            if (s5 != 0) {
                f6 = F32AT(st, 0x1C);
                if (f21 < f6) {
                    f0 = F32AT(s0, 0x80);
                    f4 = F32AT(s0, 0x84);
                    f5 = F32AT(s0, 0x88);
                    f2 = F32AT(s0, 0xA0);
                    f1 = F32AT(s0, 0xA4);
                    f3 = F32AT(s0, 0xA8);
                    f2 = (f2 - f0) * f6 + f0;
                    F32AT(s0, 0x80) = f2;
                    f1 = (f1 - f4) * f6 + f4;
                    F32AT(s0, 0x84) = f1;
                    F32AT(s0, 0x8C) = f20;
                    f3 = (f3 - f5) * f6 + f5;
                    F32AT(s0, 0x88) = f3;
                    Quat_Slerp(f6, s0 + 0x90, s0 + 0x90, s0 + 0xB0);
                }
            }
        } else {
            func_003126C8(s0 + 0x80, s4 + 0x30);
            S32AT(s0, 0x90) = 0;
            F32AT(s0, 0x9C) = f20;
            S32AT(s0, 0x94) = 0;
            S32AT(s0, 0x98) = 0;
        }

        v0 = U16AT(s4, 6);
        if (v0 != 0) {
            break;
        }
        s4 += S32AT(s4, 0);
    }
}
