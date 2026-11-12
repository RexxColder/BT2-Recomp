#include "common.h"
#include "m2c_macros.h"

/* cvt.w.s: truncates toward zero */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(x) ((s32)(x))

extern u8 func_001588E0[] __attribute__((section(".data")));
extern f32 D_003846B8;

void *func_001F3758(void *a0);
f32 func_0030D658(f32 farg0, f32 farg1);
f32 func_00152958(void *a0);
s32 func_00182A80(void *a0);
void func_001EEEF0(void *a0, void *a1);
void func_001EEDB8(void *a0, void *a1, f32 farg0);
void Vec3_Add(void *a0, void *a1, void *a2);
void Vec3_Set(void *a0, f32 farg0, f32 farg1, f32 farg2);
void Vec4_Set(void *a0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129B58(void *a0, void *a1, void *a2);
s32 func_00129C28(void *a0, void *a1);
f32 func_00212970(void);

void func_00158AD8(void *arg0) {
    u8 sp[0xA0];
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    u8 *p;
    s32 s0v;
    s32 v14;
    s32 h;
    s32 i;
    s32 t;
    f32 f0;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f14;

    s2 = M2C_FIELD(arg0, u8 **, 0x38);
    s0v = M2C_FIELD(func_001F3758(arg0), s32 *, 0x38);
    s3 = M2C_FIELD(s2, u8 **, 0x8);
    v14 = M2C_FIELD(s2, s32 *, 0x14);
    h = v14 - v14 / 2;
    f20 = func_0030D658(M2C_FIELD(s2, f32 *, 0xAB4), (f32)h);
    s4 = s2 + 0xB0;

    if (v14 < M2C_FIELD(s2, s32 *, 0xAB0)) {
        sp[0x00] = 1;
        sp[0x01] = *(u8 *)(s2 + 0x14);
        f0 = (f32)v14 * (M2C_FIELD(s2, f32 *, 0xABC) * 30.0f);
        if (f0 >= 2147483648.0f) {
            t = CVT_W_S(f0 - 2147483648.0f);
        } else {
            t = CVT_W_S(f0);
        }
        sp[0x02] = (u8)t;
        *(u16 *)(sp + 0x04) = (u16)CVT_W_S(M2C_FIELD(s3, f32 *, 0x10) * 30.0f);
        *(f32 *)(sp + 0x08) = M2C_FIELD(M2C_FIELD(s3, u8 **, 0x24), f32 *, 0x4) * f20;
        f0 = func_00152958(s4);
        s5 = sp + 0x30;
        *(f32 *)(sp + 0x0C) = M2C_FIELD(M2C_FIELD(s3, u8 **, 0x24), f32 *, 0x4) * f20 * f0;
        sp[0x10] = 0;
        sp[0x11] = 1;
        sp[0x12] = 0;
        sp[0x13] = 0;
        sp[0x14] = 0;
        sp[0x15] = 0;
        *(u32 *)(sp + 0x18) = (u32)(s64)func_001588E0;
        *(s32 *)(sp + 0x1C) = 0;
        *(s32 *)(sp + 0x20) = (s32)(s64)arg0;
        *(s32 *)(sp + 0x24) = s0v;
        *(s32 *)(sp + 0x28) = (s32)(s64)s3;
        /* 14 args: a0..a2 from the asm, a3 and t0..t3 garbage after the first jal (GUESS 0),
           then the six 8-byte stack slots at sp+0..0x28 */
        ((s32 (*)(void *, void *, s32, s32, s32, s32, s32, s32,
                  s64, s64, s64, s64, s64, s64))func_00129C28)(
            s5, s2 + 0x80, 1, 0, 0, 0, 0, 0,
            *(s64 *)(sp + 0x00), *(s64 *)(sp + 0x08), *(s64 *)(sp + 0x10),
            *(s64 *)(sp + 0x18), *(s64 *)(sp + 0x20), *(s64 *)(sp + 0x28));

        if (v14 != 0) {
            f21 = 0.0f;
            f0 = func_00152958(s4);
            f20 = M2C_FIELD(M2C_FIELD(s3, u8 **, 0x24), f32 *, 0x4) * f0;
            if (h >= 0) {
                f22 = 0.5f;
                i = 0;
                do {
                    f0 = f20 * func_0030D658(M2C_FIELD(s2, f32 *, 0xAB4), (f32)i);
                    if (i == 0 || i == h) {
                        f0 = f0 * f22;
                    }
                    i += 1;
                    f21 = f21 + f0;
                } while (h >= i);
            }
            f0 = (f32)((M2C_FIELD(s2, s32 *, 0x14) % 2) * 2 - 1);
            p = sp + 0x80;
            f21 = f21 * f0;
            func_001EEEF0(p, s2 + 0xA0);
            *(s32 *)(sp + 0x84) = 0;
            func_001EEDB8(p, p, f21);
            Vec3_Add(s5, s5, p);
            if (M2C_FIELD(s2, f32 *, 0xAB8) != 0.0f) {
                f0 = func_00152958(s4);
                f20 = M2C_FIELD(M2C_FIELD(s3, u8 **, 0x24), f32 *, 0x4) * f0;
                f20 = f20 * M2C_FIELD(s2, f32 *, 0xAB8);
                f22 = f20 + f20;
                f23 = func_00212970() * f22;
                f21 = func_00212970() * f22;
                f0 = func_00212970() * f22;
                p = sp + 0x90;
                f23 = f23 - f20;
                f21 = f21 - f20;
                f14 = f0 - f20;
                f21 = f21 + f20;
                Vec3_Set(p, f23, f21, f14);
                Vec3_Add(s5, s5, p);
            }
        }

        /* DBC / DC0 */
        p = sp + 0x40;
        f20 = 0.0f;
        func_00129C28(p, s5);
        Vec4_Set(sp + 0x60, f20, -1.0f, f20, 1.0f);
        func_00129B58(sp + 0x50, p, sp + 0x60);
        f0 = D_003846B8;
        *(f32 *)(sp + 0x78) = f20;
        *(f32 *)(sp + 0x70) = f0;
        *(f32 *)(sp + 0x74) = f0;
        *(f32 *)(sp + 0x7C) = f20;
        t = func_00182A80(sp);
        v14 = M2C_FIELD(s2, s32 *, 0x14);
        *(s32 *)(s2 + 0xC + v14 * 4) = t;
        if (*(s32 *)(s2 + 0xC + v14 * 4) != 0) {
            M2C_FIELD(s2, s32 *, 0x10) = M2C_FIELD(s2, s32 *, 0x10) + 1;
        }
        M2C_FIELD(s2, s32 *, 0x14) = v14 + 1;
        if (v14 + 1 < M2C_FIELD(s2, s32 *, 0xAB0)) {
            func_00158AD8(arg0);
        }
    }
}
