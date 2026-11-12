#include "common.h"

s32 EftShot_TestBits(s32 a0, s32 a1);
void Vec3_Normalize(void *dst, void *src);
void Vec4_Set(void *dst, f32 f12, f32 f13, f32 f14, f32 f15);
void func_0016DB58(void *a0, s32 a1, s32 a2, s32 a3, void *t0, f32 f12, f32 f13, f32 f14);
void func_00191688(s32 a0);
void func_00208F18(s32 a0, void *a1, s32 a2);

void func_0016E400(u8 *arg0) {
    f32 spf[16];
    s32 s1;
    s32 s4;
    s32 s5;
    s32 s6;
    u8 *s2;
    s32 *p;
    u8 *q;
    u8 *e;
    s32 a0v;
    s32 v1;
    f32 f0v;

    s4 = 1;
    s5 = 2;
    s6 = 4;
    s2 = *(u8 **)(arg0 + 0x38);
    p = *(s32 **)(s2 + 0xB0);
    s1 = EftShot_TestBits(*p, 4) != 0;
    if (EftShot_TestBits(*p, 0x10) != 0) {
        s1 = 1;
        s6 = 0x10;
        s5 = 4;
        s4 = 4;
    }
    if (s1 != 0) {
        func_00208F18(*p, spf, 0x36);
        q = s2 + 0x30;
        Vec4_Set(q, -spf[8], -spf[9], -spf[10], 1.0f);
        Vec3_Normalize(q, q);
        func_0016DB58(arg0, s6, s5, s4, q, 1.0f, *(f32 *)(s2 + 0x1C), *(f32 *)(s2 + 0x18));
    }
    e = s2 + 0xAC0;
    s1 = 13;
    do {
        a0v = *(s32 *)(e + 0x20);
        if (a0v != 0) {
            v1 = *(s32 *)(e + 0);
            if ((v1 & 4) == 0) {
                f0v = *(f32 *)(e + 8);
                if (8.0f <= f0v) {
                    *(s32 *)(e + 0) = v1 | 4;
                    func_00191688(a0v);
                } else {
                    f0v = f0v + 1.0f;
                    *(f32 *)(e + 8) = f0v;
                }
            }
        }
        s1 -= 1;
        e += 0x30;
    } while (s1 >= 0);
}
