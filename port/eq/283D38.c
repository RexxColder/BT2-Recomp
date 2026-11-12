#include "common.h"

void Vu0Screen_StoreMtx(s32 arg0);
void func_00312518(s32 arg0, s32 arg1);
void func_00312680(f32 farg0, s32 arg0, s32 arg1);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
void func_003125D0(f32 farg0, s32 arg0, s32 arg1);
void func_00312700(s32 arg0, s32 arg1);
void func_00283A20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s64 t0);
extern u8 D_00376E30[] __attribute__((section(".data")));
extern u8 gGfxLens[] __attribute__((section(".data")));

#define SW(o) (*(s32 *)(sp + (o)))
#define SF(o) (*(f32 *)(sp + (o)))

void func_00283D38(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[0x1f8];   /* tamano de locales del original (antes 0x1e8) */
    u8 *s0;
    u8 *s3;
    s32 k;
    s32 fp;
    s32 s7;
    s32 s1;
    s32 s2;
    s32 v1;
    s32 a0;
    s32 a2;
    s32 a3v;
    s32 a1v;
    s32 t0v;
    s32 a3b;
    s32 cond;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;

    SW(0x1E4) = arg2;
    SW(0x1E0) = arg1 & 0xFF;
    for (k = 0; k < 0x70; k++) {
        sp[0x40 + k] = D_00376E30[k];
    }
    Vu0Screen_StoreMtx((s32)(sp + 0x1A0));
    func_00312518((s32)sp, arg0);
    fp = 0;
    s7 = 7;
    do {
        s3 = gGfxLens + fp;
        v1 = *(s32 *)(s3 + 0x10);
        if (v1 != 0) {
            if (*(s32 *)(s3 + 0x24) == 0) {
                v1 = v1 - 1;
                *(s32 *)(s3 + 0x10) = v1;
            }
            f2 = *(f32 *)(s3 + 0x1C);
            f21 = f2 * 0.5f;
            f1 = (f32)v1;
            f3 = (f32)*(s32 *)(s3 + 0x14);
            f20 = (f1 / f3) * f2;
            f22 = 0.5f;
            f23 = 1.0f;
            s0 = sp + 0xB0;
            s1 = 0;
            s2 = 0;
            do {
                k = s2;
                s2 += 1;
                if (k < 5) {
                    func_00312680(f20, (s32)(sp + 0xB0 + s1), (s32)(sp + 0x40 + s1));
                } else {
                    func_00312680(f21 + (f20 * f22), (s32)(sp + 0xB0 + s1), (s32)(sp + 0x40 + s1));
                }
                s1 += 0x10;
                sceVu0ApplyMatrix((s32)s0, (s32)sp, (s32)s0);
                func_00312638((s32)s0, (s32)s3, (s32)s0);
                *(f32 *)(s0 + 0xC) = f23;
                s0 += 0x10;
            } while (s2 < 7);

            s2 = 0;
            do {
                s1 = s2 * 0x10;
                sceVu0ApplyMatrix((s32)(sp + 0x190), (s32)(sp + 0x1A0), (s32)(sp + 0xB0 + s1));
                s2 += 1;
                f0 = SF(0x19C);
                func_003125D0(f0, (s32)(sp + 0x190), (s32)(sp + 0x190));
                func_00312700((s32)(sp + 0x120 + s1), (s32)(sp + 0x190));
            } while (s2 < 7);

            a0 = 0;
            if (SW(0x168) > 0) {
                a3v = SW(0x120);
                a1v = SW(0x150);
                cond = (a3v < 0x7001);
                a2 = (((u32)(a3v - 0x7000)) < 0x2001) | (((u32)(a1v - 0x7000)) < 0x2001);
                if (cond) {
                    a2 |= (0x8FFF < a1v);
                }
                if (a1v < 0x7001) {
                    a2 |= (0x8FFF < a3v);
                }
                t0v = SW(0x124);
                a3b = SW(0x154);
                if (((u32)(t0v - 0x7200)) < 0x1C01) {
                    a2 = a2 | 2;
                }
                if (((u32)(a3b - 0x7200)) < 0x1C01) {
                    a2 = a2 | 2;
                }
                if (t0v < 0x7201) {
                    if (0x8DFF < a3b) {
                        a2 = a2 | 2;
                    }
                }
                if (a3b < 0x7201) {
                    if (0x8DFF < t0v) {
                        a2 = a2 | 2;
                    }
                    a0 = (a2 ^ 3) == 0;
                } else {
                    a0 = (a2 ^ 3) == 0;
                }
            }
            if (a0 != 0) {
                func_00283A20((s32)(sp + 0x120), SW(0x1E0), SW(0x1E4), *(s32 *)(s3 + 0x18), *(s32 *)(s3 + 0x20));
            }
        }
        s7 -= 1;
        fp += 0x30;
    } while (s7 >= 0);
}
