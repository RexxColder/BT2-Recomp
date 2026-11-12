#include "common.h"

extern f32 D_00383ECC;
extern f32 D_00383ED0;
extern f32 D_00383ED4;
extern f32 D_00383ED8;

void *func_0010B080(void);
void func_00112B60(s32 a, s32 b, void *c, void *d);
s32 func_0020B6E0(void *a);
s32 func_0020B7A0(void *a);
s32 func_0020B7E0(void *a);
void Ramp_Start(void *p, f32 a, f32 b, f32 c);
s32 Ramp_Step(void *p);
void func_00113BE0(void *a, s32 b);
void func_00113860(void *a, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_00113D80(void *a, s32 b);
s32 func_001114C0(void *a, s32 b, s32 c);
void func_00113B50(void *a, s32 b, s32 c, s32 d);
void func_0029D548(void);
void func_00113598(void *a);
void func_00113760(void *a, s32 b);
void func_0029D580(s32 a);
void func_00113430(s32 a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);

f32 func_00111D00(s32 arg0, void *arg1, void *arg2) {
    u8 sp[0x2C0];
    void *s5;
    s32 s3;
    s32 s4;
    s32 i;
    f32 f20;
    f32 f0;
    u8 *s0;

    s5 = func_0010B080();
    func_00112B60(*(s32 *)((u8 *)s5 + 4), 2, sp + 0x2B0, sp + 0x2B4);
    f20 = -(f32)*(s32 *)(sp + 0x2B0);
    s3 = func_0020B6E0(arg2);

    if (*(u8 *)((u8 *)arg1 + 1) == 0) {
        if (s3 > 0 || func_0020B7E0(arg2) != 0) {
            *(u8 *)((u8 *)arg1 + 1) = 1;
        }
        if (*(u8 *)((u8 *)arg1 + 1) == 0) {
            *(f32 *)((u8 *)arg1 + 0x1C) = f20;
            return 32.0f;
        }
    }

    /* block B */
    s3 = func_0020B6E0(arg2);
    f0 = *(f32 *)((u8 *)arg1 + 0x1C);
    if (func_0020B7A0(arg2) == 0) {
        f0 = f0 - D_00383ECC;
        *(f32 *)((u8 *)arg1 + 0x1C) = f0;
        if (f0 < f20) {
            *(f32 *)((u8 *)arg1 + 0x1C) = f20;
            *(u8 *)((u8 *)arg1 + 1) = 0;
            return 32.0f;
        }
    } else {
        f0 = f0 + D_00383ED0;
        *(f32 *)((u8 *)arg1 + 0x1C) = f0;
        if (0.0f < f0) {
            *(f32 *)((u8 *)arg1 + 0x1C) = 0.0f;
        }
    }

    s0 = (u8 *)arg1 + 0x5C;
    if (func_0020B7E0(arg2) != 0) {
        Ramp_Start(s0, D_00383ED4, 0.0f, 1.0f);
    }
    if (Ramp_Step(s0) != 0 && *(f32 *)((u8 *)arg1 + 0x6C) == 1.0f) {
        Ramp_Start(s0, D_00383ED8, 1.0f, 0.0f);
    }

    func_00113BE0(sp + 0x240, 1);
    func_00113860(sp + 0xC, 0, (s32)((u32)*(s32 *)(sp + 0x2B4) << 15) >> 16,
                  *(s16 *)(sp + 0x2B0), *(s16 *)(sp + 0x2B4), 2);
    func_00113D80(sp, 0);
    s4 = func_001114C0(sp + 0x60, s3, 5);

    {
        u8 *a0 = sp + 0x60;
        s0 = sp + 0x60;
        i = 4;
        do {
            s0 += 0x60;
            i -= 1;
            func_00113D80(a0, 0);
            a0 = s0;
        } while (i >= 0);
    }

    func_00113B50(sp + 0x60, 0, 0x2C, 0);
    func_00113B50(sp + s4 * 0x60 + 0xC0, 1, 0xE, 0);

    if ((arg0 & 0xFF) == 0) {
        *(f32 *)(sp + 0x2A0) = f20 - (*(f32 *)((u8 *)arg1 + 0x1C) + *(f32 *)((u8 *)arg1 + 0x6C) * 10.0f);
        *(s32 *)(sp + 0x2A4) = 0;
    } else {
        *(s32 *)(sp + 0x2A4) = 0;
        *(f32 *)(sp + 0x2A0) = *(f32 *)((u8 *)arg1 + 0x1C) - (*(f32 *)((u8 *)arg1 + 0x6C) * 10.0f);
    }

    func_0029D548();
    func_00113598(sp + 0x2A0);
    func_00113760(sp, 1);
    func_0029D580(1);
    func_00113430(*(s32 *)((u8 *)s5 + 4), sp, 1, 0x2A00, 0x2C00, 0, 0);
    return 32.0f;
}
