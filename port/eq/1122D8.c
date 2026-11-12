#include "common.h"

extern f32 D_00383EEC;
extern f32 D_00383EF0;
extern f32 D_00383EF4;
extern f32 D_00383EF8;

void *func_0010B080(void);
void func_00112B60(s32 arg0, s32 arg1, void *arg2, void *arg3);
s32 func_0020A168(s32 arg0);
void Ramp_Start(void *arg0, f32 farg0, f32 farg1, f32 farg2);
s32 Ramp_Step(void *arg0);
void func_00113BE0(void *arg0, s32 arg1);
void func_00113860(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113D80(void *arg0, s32 arg1);
void func_00111328(void *arg0, s32 arg1, s32 arg2);
void func_00113B50(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0029D548(void);
void func_00113598(void *arg0);
void func_00113620(void *arg0, s32 arg1);
void func_00113600(f32 farg0, f32 farg1);
void func_00113F28(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0029D580(s32 arg0);
void func_00113430(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

f32 func_001122D8(s32 arg0, u8 *arg1, s32 arg2) {
    u8 sp[0x1A0];
    u8 *s4;
    u8 *s0;
    u8 *a0p;
    f32 f20;
    f32 f0;
    s32 s2;
    s32 s3;
    s32 v1;

    s4 = (u8 *)func_0010B080();
    func_00112B60(*(s32 *)(s4 + 4), 2, sp + 0x190, sp + 0x194);
    f20 = -(f32)*(s32 *)(sp + 0x190);
    v1 = arg1[2];
    s2 = func_0020A168(arg2);
    if (v1 == 0) {
        if (s2 >= 2) {
            v1 = 1;
            arg1[2] = 1;
        }
        if (v1 == 0) {
            *(f32 *)(arg1 + 0x24) = f20;
            goto end;
        }
    }

    s2 = func_0020A168(arg2);
    if ((u32)s2 < 2U) {
        s2 = *(s32 *)(arg1 + 0x8);
        f0 = *(f32 *)(arg1 + 0x24) - D_00383EEC;
        *(f32 *)(arg1 + 0x24) = f0;
        if (f0 < f20) {
            *(f32 *)(arg1 + 0x24) = f20;
            arg1[2] = 0;
            goto end;
        }
    } else {
        f0 = *(f32 *)(arg1 + 0x24) + D_00383EF0;
        *(f32 *)(arg1 + 0x24) = f0;
        if (f0 > 0.0f) {
            *(f32 *)(arg1 + 0x24) = 0.0f;
        }
    }

    s0 = arg1 + 0x44;
    if (*(s32 *)(arg1 + 0x8) != s2) {
        Ramp_Start(s0, D_00383EF4, 0.0f, 1.0f);
    }
    *(s32 *)(arg1 + 0x8) = s2;
    if (Ramp_Step(s0) != 0 && *(f32 *)(arg1 + 0x54) == 1.0f) {
        Ramp_Start(s0, D_00383EF8, 1.0f, 0.0f);
    }

    func_00113BE0(sp + 0x120, 1);
    s3 = 1;
    func_00113860(sp + 0xC, 0, 0, *(s16 *)(sp + 0x190),
                  (s32)((u32)*(s32 *)(sp + 0x194) << 15) >> 16, 2);
    func_00113D80(sp, 0);
    func_00111328(sp + 0x60, s2, 2);
    s0 = sp + 0x60;
    a0p = s0;
    do {
        s0 += 0x60;
        s3 -= 1;
        func_00113D80(a0p, 0);
        a0p = s0;
    } while (s3 >= 0);
    func_00113B50(sp + 0x60, 0, 0xA, 0);
    func_00113B50(sp + 0xC0, 1, 0x1B, 0);

    if ((arg0 & 0xFF) == 0) {
        *(s32 *)(sp + 0x184) = 0;
        f0 = f20 - *(f32 *)(arg1 + 0x24);
    } else {
        *(s32 *)(sp + 0x180) = 0;
        f0 = *(f32 *)(arg1 + 0x24) + *(f32 *)(sp + 0x180);
        *(f32 *)(sp + 0x184) = *(f32 *)(sp + 0x180);
    }
    *(f32 *)(sp + 0x180) = f0;
    func_0029D548();
    func_00113598(sp + 0x180);
    func_00113620(sp, 1);
    func_00113600(1.0f, *(f32 *)(arg1 + 0x54) + 1.0f);
    func_00113620(sp + 0x60, 1);
    func_00113620(sp + 0xC0, 1);
    func_00113F28(sp + 0x60, -1, -1, -1, *(s16 *)(sp + 0x44));
    func_0029D580(1);
    func_00113430(*(s32 *)(s4 + 4), sp, 1, 0x2A00, 0x2C00, 0, 0);

end:
    return 32.0f;
}
