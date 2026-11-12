#include "common.h"

#define F(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
s32 func_001B8088(s32 arg0);
void func_001B80F0(f32 farg0, s32 arg1);
void func_001B8510(s32 arg0, s32 arg1);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(f32 farg0, s32 arg1, s32 arg2);
s32 rand(void);

extern u8 *D_003876A0;
extern u8 D_003887D0[] __attribute__((section(".data")));
extern f32 D_00385040;
extern f32 D_00385044;
extern f32 D_00385048;
extern f32 D_0038504C;
extern f32 D_00385050;
extern f32 D_00385054;

void func_001B7D58(u8 *arg0) {
    u8 sp[0x20];
    u8 *s3;
    u8 *s0;
    u8 *s1;
    s32 s2;
    s32 v;
    s32 flag;
    f32 f26;
    f32 f25;
    f32 f22;
    f32 f24;
    f32 f23;
    f32 f20;
    f32 f21;
    f32 t;

    s3 = (u8 *)W(arg0, 0x38);
    f26 = F(s3, 0x48);
    if ((*(s64 *)(D_003876A0 + 0x4D8)) & 0x100) {
        return;
    }

    f25 = D_00385040;
    f22 = 10.0f;
    f24 = -15.0f;
    f23 = 1.0f;
    s0 = D_003887D0;
    s2 = 0;
    do {
        f20 = (f32)s2;
        s2 += 1;
        f21 = f20 * f25;
        f20 = f24 - f20;
        t = sinf(f21) * f22;
        F(s0, 4) = f20;
        F(s0, 0) = t;
        t = cosf(f21) * f22;
        F(s0, 0xC) = f23;
        F(s0, 8) = t;
        s0 += 0x10;
    } while (s2 < 0x20);

    F(s3, 0x54) = F(s3, 0x54) + 1.0f;
    v = func_001B8088((s32)s3);
    if (v > 0) {
        f22 = D_00385044;
        f21 = 6.0f;
        f20 = 4.0f;
        s2 = v;
        do {
            s2 -= 1;
            t = ((f32)rand() / f22) * f21 + f20;
            func_001B80F0(t, (s32)s3);
        } while (s2 != 0);
    }
    s1 = (u8 *)W(s3, 0x68);

    s2 = 9;
    f20 = 1.0f;
    do {
        flag = W(s1, 0x5C) & 1;
        s0 = s1 + 0x20;
        if (flag) {
            func_00312680(f26, (s32)s0, (s32)s0);
            func_00312680(D_00385048, (s32)sp, (s32)(s3 + 0x20));
            func_00312638((s32)s0, (s32)s0, (s32)sp);

            F(sp, 0x10) = sinf(F(s1, 0x48)) * F(s1, 0x4C);
            F(sp, 0x14) = F(s1, 0x54);
            t = cosf(F(s1, 0x48));
            F(sp, 0x1C) = f20;
            F(sp, 0x18) = t * F(s1, 0x4C);

            t = F(s1, 0x48) + F(s1, 0x44);
            F(s1, 0x48) = t;
            if (D_0038504C < t) {
                F(s1, 0x48) = t - D_0038504C;
            }
            func_00312638((s32)s1, (s32)s3, (s32)(sp + 0x10));
            F(s1, 0x54) = F(s1, 0x54) - D_00385050;
            F(s1, 0x4C) = F(s1, 0x4C) + D_00385054;
            func_001B8510((s32)s3, (s32)s1);
        }
        s2 -= 1;
        s1 += 0x60;
    } while (s2 >= 0);
}
