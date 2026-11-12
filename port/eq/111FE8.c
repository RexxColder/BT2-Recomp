#include "common.h"

extern f32 D_00383EDC;
extern f32 D_00383EE0;
extern f32 D_00383EE4;
extern f32 D_00383EE8;

void *func_0010B080(s32 a0);
void func_00112B60(s32 a0, s32 a1, s32 *a2, s32 *a3);
s32 func_0020B720(void *a0);
s32 func_0020B6A0(void *a0);
s32 func_0020B7A0(void *a0);
s32 func_0020B7E0(void *a0);
void Ramp_Start(void *p, f32 a, f32 b, f32 c);
s32 Ramp_Step(void *p);
void func_00113BE0(void *p, s32 a1);
void func_00113860(void *a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1);
void func_00113D80(void *a0, s32 a1);
void func_00111328(void *a0, s32 a1, s32 a2);
void func_00113B50(void *a0, s32 a1, s32 a2, s32 a3);
void func_0029D548();
void func_00113598(void *p);
void func_00113620(void *a0, s32 a1);
void func_00113600(f32 a, f32 b);
void func_00113F28(void *a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_0029D580(s32 a0);
void func_00113430(s32 a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);

f32 func_00111FE8(s32 arg0, u8 *arg1, void *arg2) {
    s64 fr[60];
    u8 *sp;
    void *s0;
    void *s4;
    u8 *p60;
    u8 *pC0;
    u8 *ptr;
    s32 s2;
    s32 s3;
    s32 s5;
    s32 tmp;
    f32 f0;
    f32 f20;

    sp = (u8 *)fr;
    s0 = arg2;
    s5 = arg0 & 0xFF;
    s4 = func_0010B080(arg0);
    func_00112B60(*(s32 *)((u8 *)s4 + 4), 2, (s32 *)(sp + 0x190), (s32 *)(sp + 0x194));
    f20 = -(f32)*(s32 *)(sp + 0x190);
    s3 = func_0020B720(s0);

    if (*arg1 == 0) {
        if (s3 >= 2) {
            *arg1 = 1;
        }
        if (*arg1 == 0) {
            *(f32 *)(arg1 + 0x14) = f20;
            return 32.0f;
        }
    }

    s3 = func_0020B6A0(s0);
    if (func_0020B7A0(s0) != 0 && s3 != 1) {
        if (s3 != 0) {
            f0 = *(f32 *)(arg1 + 0x14) + D_00383EE0;
            *(f32 *)(arg1 + 0x14) = f0;
            if (0.0f < f0) {
                *(f32 *)(arg1 + 0x14) = 0.0f;
            }
            goto block_15;
        }
    }

    s3 = *(s32 *)(arg1 + 4);
    f0 = *(f32 *)(arg1 + 0x14) - D_00383EDC;
    *(f32 *)(arg1 + 0x14) = f0;
    if (f0 < f20) {
        *(f32 *)(arg1 + 0x14) = f20;
        *arg1 = 0;
        return 32.0f;
    }

block_15:
    *(s32 *)(arg1 + 4) = s3;
    tmp = func_0020B7E0(s0);
    s0 = arg1 + 0x2C;
    if (tmp != 0) {
        Ramp_Start(s0, D_00383EE4, 0.0f, 1.0f);
    }
    if (Ramp_Step(s0) != 0) {
        if (*(f32 *)(arg1 + 0x3C) == 1.0f) {
            Ramp_Start(s0, D_00383EE8, 1.0f, 0.0f);
        }
    }

    func_00113BE0(sp + 0x120, 1);
    func_00113860(sp + 0xC, 0, 0, (s16)*(s32 *)(sp + 0x190),
                  ((s32)((u32)*(s32 *)(sp + 0x194) << 15)) >> 16, 2);
    func_00113D80(sp, 0);

    p60 = sp + 0x60;
    func_00111328(p60, s3, 2);
    s0 = p60;
    ptr = (u8 *)s0;
    s2 = 1;
    do {
        s0 = (u8 *)s0 + 0x60;
        s2 -= 1;
        func_00113D80(ptr, 0);
        ptr = (u8 *)s0;
    } while (s2 >= 0);

    func_00113B50(p60, 0, 0xA, 0);
    pC0 = sp + 0xC0;
    func_00113B50(pC0, 1, 0x1B, 0);

    if (s5 == 0) {
        *(f32 *)(sp + 0x184) = 0.0f;
        f0 = f20 - *(f32 *)(arg1 + 0x14);
    } else {
        *(f32 *)(sp + 0x180) = 0.0f;
        f0 = *(f32 *)(arg1 + 0x14) + *(f32 *)(sp + 0x180);
        *(f32 *)(sp + 0x184) = *(f32 *)(sp + 0x180);
    }
    *(f32 *)(sp + 0x180) = f0;
    func_0029D548();
    func_00113598(sp + 0x180);
    func_00113620(sp, 1);
    func_00113600(1.0f, *(f32 *)(arg1 + 0x3C) + 1.0f);
    func_00113620(p60, 1);
    func_00113620(pC0, 1);
    func_00113F28(p60, -1, -1, -1, *(s16 *)(sp + 0x44));
    func_0029D580(1);
    func_00113430(*(s32 *)((u8 *)s4 + 4), sp, 1, 0x2A00, 0x2C00, 0, 0);
    return 32.0f;
}
