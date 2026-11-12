#include "common.h"

extern f32 D_00383F78;
extern f32 D_00383F7C;
extern f32 D_00383F80;
extern f32 D_00383F84;
extern f32 D_00383F88;

s32 func_0010B078(void);
s32 func_0010B080(void);
void func_00113CB8(u8 *arg0, s32 arg1, s32 arg2, s16 arg3);
void func_00113BE0(u8 *arg0, s32 arg1);
void Ramp_Start(u8 *arg0, f32 farg0, f32 farg1, f32 farg2);
s32 Ramp_Step(u8 *arg0);
void func_00113A30(u8 *arg0, u8 *arg1);
void func_0029D548();
void func_00113548(u8 *arg0, f32 farg0);
void func_00113600(f32 farg0, f32 farg1);
void func_00113620(u8 *arg0, s32 arg1);
void func_0029D580(s32 arg0);
void func_00112B28(s32 arg0);
void func_00113430(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void HudNotice_GsBeginAdd();
void HudNotice_GsEndAdd();

/* float -> u32 conversion with the 2^31 split */
static u32 f2u(f32 v) {
    u32 r = (u32)(s32)v;
    if (v >= 2147483648.0f) {
        r = (u32)(s32)(v - 2147483648.0f) | 0x80000000;
    }
    return r;
}

/* HUD notice animation (6 states at obj+0): fades two panel layers in / out with the ramps at obj+4 and
   obj+0x1C, drawing three copies of the panel (sp, sp+0x60, sp+0xC0). Returns 1 in state 5, else 0. */
s32 func_00117D10(void) {
    u8 sp[0x200];
    u8 *obj;
    s32 *gs;
    u8 *ramp;
    u8 *ramp2;
    s32 scaleSet = 0;   /* panel 2 drawn (s5) */
    s32 active = 0;     /* panel 1 visible (s6) */
    f32 scaleA = 1.0f;
    f32 scaleB = 1.0f;
    f32 scaleC = 1.0f;
    s32 st;
    s32 v;

    obj = (u8 *)func_0010B078() + 0x3C;
    gs = (s32 *)func_0010B080();
    func_00113CB8(sp, 1, *gs, 2);
    func_00113CB8(sp + 0x60, 1, *gs, 2);
    func_00113BE0(sp + 0x120, 1);
    *(s32 *)(obj + 0x34) = 0;
    st = *(s32 *)obj;
    *(s32 *)(obj + 0x38) = 0;

    switch (st) {
    case 0:
        ramp = obj + 4;
        ramp2 = obj + 0x1C;
        Ramp_Start(ramp, D_00383F78, 0.0f, 1.0f);
        Ramp_Start(ramp2, D_00383F7C, 1.0f, 0.0f);
        *(s32 *)obj = *(s32 *)obj + 1;
        goto step1;
    case 1:
        ramp = obj + 4;
        ramp2 = obj + 0x1C;
    step1:
        active = 1;
        if (Ramp_Step(ramp) != 0) {
            sp[0x78] = 0x80;
            sp[0x16] = 0x80;
            sp[0x17] = 0x80;
            sp[0x18] = 0x80;
            sp[0x19] = 0x80;
            sp[0x76] = 0x80;
            sp[0x77] = 0x80;
        } else {
            v = f2u(*(f32 *)(obj + 0x14) * 128.0f);
            sp[0x19] = v;
            sp[0x78] = 0xFF - v;
            sp[0x16] = 0xFF - v;
            sp[0x17] = 0xFF - v;
            sp[0x18] = 0xFF - v;
            sp[0x76] = 0xFF - v;
            sp[0x77] = 0xFF - v;
        }
        if (Ramp_Step(ramp2) != 0) {
            Ramp_Start(ramp, D_00383F80, 0.0f, 1.0f);
            *(s32 *)obj = *(s32 *)obj + 1;
            sp[0x79] = 0;
        } else {
            f32 b = *(f32 *)(obj + 0x2C);

            scaleB = (1.0f - b) + 1.0f;
            scaleA = scaleB;
            sp[0x79] = f2u(b * 128.0f);
        }
        break;
    case 2:
        ramp = obj + 4;
        if (Ramp_Step(ramp) == 0) {
            scaleSet = 1;
        } else {
            Ramp_Start(ramp, 0.5f, 0.0f, 1.0f);
            *(s32 *)obj = *(s32 *)obj + 1;
        }
        break;
    case 3:
        ramp = obj + 4;
        if (Ramp_Step(ramp) != 0) {
            Ramp_Start(ramp, D_00383F84, 1.0f, 0.0f);
            *(s32 *)obj = *(s32 *)obj + 1;
        }
        break;
    case 4:
        if (Ramp_Step(obj + 4) != 0) {
            sp[0x19] = 0;
            *(s32 *)obj = *(s32 *)obj + 1;
        } else {
            f32 a = *(f32 *)(obj + 0x14);

            scaleC = (1.0f - a) * D_00383F88 + 1.0f;
            sp[0x19] = f2u(a * 128.0f);
        }
        break;
    case 5:
        return 1;
    default:
        break;
    }

    *(s32 *)(sp + 0x60) = active ? *(s32 *)(sp + 0x60) : 0;
    if (scaleSet == 0) {
        *(s32 *)(sp + 0xC0) = 0;
    } else {
        __builtin_memset(sp + 0x180, 0, 8);
        __builtin_memcpy(sp + 0xC0, sp, 0x60);
        *(s16 *)(sp + 0xD4) = 7;
        *(s32 *)(sp + 0x184) = 0;
        *(s32 *)(sp + 0xC0) = *(s32 *)(sp + 0xC0) | 0x80;
        *(f32 *)(sp + 0x180) = *(f32 *)(obj + 0x14);
        func_00113A30(sp + 0xC0, sp + 0x180);
    }

    func_0029D548();
    func_00113548(obj + 0x34, 0.0f);
    func_0029D548();
    func_00113600(scaleA, scaleB);
    func_00113620(sp + 0x60, 1);
    func_0029D580(1);
    func_00113600(scaleC, scaleC);
    func_00113620(sp, 1);
    func_00113620(sp + 0xC0, 1);
    func_0029D580(1);
    func_00112B28(*gs);
    if (scaleSet == 0) {
        func_00113430(*gs, sp, 1, 0x2A00, 0x2C00, 0, 0);
        return 0;
    }
    HudNotice_GsBeginAdd();
    func_00113430(*gs, sp, 1, 0x2A00, 0x2C00, 0, 0);
    HudNotice_GsEndAdd();
    return 0;
}
