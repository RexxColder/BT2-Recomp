#include "common.h"

extern u8 D_002C3630[] __attribute__((section(".data")));
extern u8 D_0036EB10[] __attribute__((section(".data")));
extern f32 D_00384F4C;
extern f32 D_00384F50;
extern f32 D_00384F54;

f32 EftMath_WrapAngle(f32 farg0);
void func_001AF2F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10, f32 farg0, f32 farg1, f32 farg2, f32 farg3,
                   f32 farg4, f32 farg5);
void func_001B0298(f32 farg0, s32 arg0, s32 arg1);
void func_001EC310(s32 arg0, s32 arg1);
s32 rand(void);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
void sceVu0MulMatrix(s32 arg0, s32 arg1, s32 arg2);
void sceVu0RotMatrixY(f32 farg0, s32 arg0, s32 arg1);
void sceVu0TransMatrix(s32 arg0, s32 arg1, s32 arg2);
void sceVu0UnitMatrix(s32 arg0);

void func_001AF9F0(u8 *arg0) {
    u8 sp[0x140];
    u8 *s0;
    u8 *p;
    u8 *s2;
    u8 *s4;
    u8 *s6;
    u8 *fp;
    u8 *s7;
    s32 s1;
    f32 f0;
    f32 f1;
    f32 f12;
    f32 f14;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 t;

    s0 = arg0 + 0x80;
    if (*(u8 *)(s0 + 0xE0) == 0) {
        f0 = *(f32 *)(s0 + 0xDC) - 1.0f;
        *(f32 *)(s0 + 0xDC) = f0;
        if (f0 <= 0.0f) {
            *(f32 *)(s0 + 0xDC) = 0.0f;
            *(u8 *)(s0 + 0xE2) = 1;
            *(u8 *)(s0 + 0xE0) = 1;
        }
    }
    if (*(u8 *)(s0 + 0xE2) == 0) {
        return;
    }

    s2 = sp + 0x60;
    s6 = sp + 0xA0;
    s4 = sp + 0xE0;
    fp = arg0 + 0x1C0;
    s7 = arg0 + 0x1C4;
    sceVu0UnitMatrix((s32)(sp + 0x20));
    sceVu0UnitMatrix((s32)s2);
    sceVu0UnitMatrix((s32)s6);

    f1 = *(f32 *)(s0 + 0xD0);
    s1 = 2;
    p = sp + 0x20;
    do {
        *(f32 *)p = *(f32 *)p * f1;
        s1 -= 1;
        p += 0x14;
    } while (s1 >= 0);

    f12 = *(f32 *)(s0 + 0xC0) - *(f32 *)(s0 + 0xC4);
    *(f32 *)(s0 + 0xC0) = f12;
    f0 = EftMath_WrapAngle(f12);
    *(f32 *)(s0 + 0xC0) = f0;
    sceVu0RotMatrixY(f0, (s32)s2, (s32)s2);

    f12 = *(f32 *)(s0 + 0xC8);
    if (f12 != 0.0f) {
        func_001B0298(f12, (s32)s6, (s32)(arg0 + 0x30));
    }

    f22 = D_00384F4C;
    sceVu0MulMatrix((s32)s2, (s32)s6, (s32)s2);
    f21 = D_00384F50;
    f20 = 0.5f;
    sceVu0MulMatrix((s32)(sp + 0x20), (s32)(sp + 0x20), (s32)s2);
    s1 = 0;
    sceVu0TransMatrix((s32)(sp + 0x20), (s32)(sp + 0x20), (s32)arg0);
    func_001EC310((s32)(s0 + 0x40), (s32)(sp + 0x20));

    do {
        *(s64 *)s4 = *(s64 *)D_0036EB10;
        *(s64 *)(s4 + 8) = *(s64 *)(D_0036EB10 + 8);
        sceVu0UnitMatrix((s32)(sp + 0xF0));
        f12 = (f32)s1;
        s1 += 1;
        f0 = *(f32 *)(s0 + 0xC0);
        f12 = f0 + (f22 * f12);
        f0 = EftMath_WrapAngle(f12);
        sceVu0RotMatrixY(f0, (s32)(sp + 0xF0), (s32)(sp + 0xF0));
        sceVu0MulMatrix((s32)(sp + 0xF0), (s32)s6, (s32)(sp + 0xF0));
        sceVu0ApplyMatrix((s32)s4, (s32)(sp + 0xF0), (s32)s4);
        rand();
        t = (f32)rand();
        f14 = ((t / f21) * f20) + f20;
        func_001AF2F0((s32)fp, (s32)s7, *(s32 *)(arg0 + 0x44), (s32)D_002C3630, (s32)s4,
                      *(s32 *)(arg0 + 0x40), 0xFF, 0xFF, 0xFF, 0, 1,
                      5.5f, -4.0f, f14, 128.0f, D_00384F54, 0.0f);
    } while (s1 < 3);
}
