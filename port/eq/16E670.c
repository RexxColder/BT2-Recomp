#include "common.h"

s32 EftShot_TestBits(s32 a0, s32 a1);
s32 func_0020B3D0(s32 a0);
void func_00208DE8(s32 a0, s32 a1, s32 a2);
void func_0012D3A0(s32 a0, s32 a1, s32 a2);
void func_002837C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00283800(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00283840(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00283770(s32 a0, s32 a1, s32 a2);
extern f32 D_003848A0;

void func_0016E670(u8 *arg0) {
    s32 sp[4];
    u8 *O;
    u8 *s1p;
    u8 *s2;
    s32 s3;
    s32 s0;
    s32 s1;
    s32 t0;
    s32 r;
    f32 f0;
    f32 f1;
    f32 x;

    O = *(u8 **)(arg0 + 0x38);
    s1p = *(u8 **)(O + 0xB0);
    s3 = func_0020B3D0(*(s32 *)s1p);
    s2 = O + 0x30;
    if (*(s32 *)(*(u8 **)(s1p + 0x20) + 0x30) & 0x200) {
        if (EftShot_TestBits(s3, 0x10) != 0) {
            *(s32 *)O = *(s32 *)O | 0x800;
            func_00208DE8(*(s32 *)s1p, (s32)sp, 0x11);
            func_0012D3A0((s32)s2, (s32)sp, *(s32 *)s1p);
        }
        if (EftShot_TestBits(s3, 0x20) != 0) {
            *(f32 *)(O + 0x20) = 0.0f;
            *(s32 *)O = *(s32 *)O & ~0x800;
        }
        if (*(s32 *)O & 0x800) {
            f0 = *(f32 *)(O + 0x20) + D_003848A0;
            *(f32 *)(O + 0x20) = f0;
            if (1.0f < f0) {
                *(f32 *)(O + 0x20) = 1.0f;
            }
        }
    }
    f1 = *(f32 *)(O + 0x20);

    /* cvt.w.s truncates toward zero-even, written out for each of the three values */
    x = f1 * 8.0f;
    r = (s32)x;
    t0 = r;

    x = f1 * 32.0f;
    r = (s32)x;
    s0 = r;

    x = f1 * 128.0f;
    r = (s32)x;
    s1 = r;

    func_002837C0(0, 0x80, 0x80, 0x80, t0 & 0xFF);
    func_00283800(0, 0x80, 0x80, 0x80, s0 & 0xFF);
    func_00283840(0, 0x80, 0x80, 0x80, s1 & 0xFF);
    func_00283770(0, (s32)s2, 0);
}
