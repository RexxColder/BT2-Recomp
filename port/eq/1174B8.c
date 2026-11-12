#include "common.h"

extern u8 *func_0010B078(void);
extern s32 *func_0010B080(void);
extern void func_00113CB8(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00113BE0(void *arg0, s32 arg1);
extern void Ramp_Start(u8 *arg0, f32 farg0, f32 farg1, f32 farg2);
extern s32 Ramp_Step(u8 *arg0);
extern void func_00113A30(void *arg0, void *arg1);
extern void func_0029D548(void);
extern void func_00113548(u8 *arg0, f32 farg0);
extern void func_00113600(f32 farg0, f32 farg1);
extern void func_00113620(void *arg0, s32 arg1);
extern void func_0029D580(s32 arg0);
extern void HudNotice_GsBeginAdd(void);
extern void func_00112B28(s32 arg0);
extern void func_00113430(s32 a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
extern void HudNotice_GsEndAdd(void);
extern f32 D_00383F48;
extern f32 D_00383F4C;
extern f32 D_00383F50;
extern f32 D_00383F54;
extern f32 D_00383F58;
extern f32 D_00383F5C;

s32 func_001174B8(void) {
    u8 sp[0x130];
    u8 *st;
    s32 *scene;
    u8 *rampA;
    u8 *rampB;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 t;
    f32 sc;
    s32 state;

    st = func_0010B078();
    scene = func_0010B080();
    func_00113CB8(sp, 1, *scene, 0);
    func_00113BE0(sp + 0xC0, 1);
    f22 = 1.0f;
    f24 = f22;
    f23 = 0.0f;
    state = *(s32 *)st;
    if (state >= 5) {
        goto draw;
    }
    switch (state) {
    case 0:
        rampA = st + 4;
        rampB = st + 0x1C;
        Ramp_Start(rampA, D_00383F48, 0.0f, 1.0f);
        Ramp_Start(rampB, D_00383F4C, 0.0f, 1.0f);
        *(f32 *)(st + 0x34) = 0.0f;
        *(f32 *)(st + 0x38) = 0.0f;
        *(s32 *)st = *(s32 *)st + 1;
        goto step;
    case 1:
        rampA = st + 4;
        rampB = st + 0x1C;
    step:
        Ramp_Step(rampA);
        sp[0x19] = 0x80;
        if (Ramp_Step(rampB) == 0) {
            t = 1.0f - *(f32 *)(st + 0x2C);
            f23 = t * D_00383F54;
            f22 = t * 3.0f + 1.0f;
            f24 = f22;
        } else {
            Ramp_Start(rampB, D_00383F50, 0.0f, 1.0f);
            *(s32 *)st = *(s32 *)st + 1;
        }
        break;
    case 2:
        if (Ramp_Step(st + 0x1C) != 0) {
            Ramp_Start(st + 4, D_00383F58, 1.0f, 0.0f);
            *(s32 *)st = *(s32 *)st + 1;
        }
        break;
    case 3:
        if (Ramp_Step(st + 4) != 0) {
            sp[0x19] = 0;
            *(s32 *)st = *(s32 *)st + 1;
        } else {
            sc = *(f32 *)(st + 0x14) * 128.0f;
            if (sc >= 2147483648.0f) {
                sp[0x19] = (u8)((u32)(s32)(sc - 2147483648.0f) | 0x80000000U);
            } else {
                sp[0x19] = (u8)(s32)sc;
            }
            f22 = (1.0f - *(f32 *)(st + 0x14)) * D_00383F5C + 1.0f;
        }
        break;
    case 4:
        return 1;
    }
draw:
    __builtin_memcpy(sp + 0x60, sp, 0x60);
    *(s16 *)(sp + 0x74) = 7;
    *(s32 *)(sp + 0x60) |= 0x80;
    if (*(s32 *)st == 2) {
        __builtin_memset(sp + 0x120, 0, 8);
        *(s32 *)(sp + 0x124) = 0;
        *(f32 *)(sp + 0x120) = *(f32 *)(st + 0x2C);
        func_00113A30(sp + 0x60, sp + 0x120);
    }
    func_0029D548();
    func_00113548(st + 0x34, f23);
    func_00113600(f24, f22);
    func_00113620(sp, 1);
    func_00113620(sp + 0x60, 1);
    func_0029D580(1);
    HudNotice_GsBeginAdd();
    func_00112B28(*scene);
    func_00113430(*scene, sp, 1, 0x2A00, 0x2C00, 0, 0);
    HudNotice_GsEndAdd();
    return 0;
}
