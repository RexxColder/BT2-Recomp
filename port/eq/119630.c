#include "common.h"

extern f32 D_00384010;
extern f32 D_00384014;
extern f32 D_00384018;
extern f32 D_0038401C;

s32 func_0010B078(void);
s32 func_0010B080(void);
void func_00113860(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113D80(u8 *arg0, s32 arg1);
s32 func_00113B00(u8 *arg0, s32 arg1, s32 arg2);
void func_00113BE0(u8 *arg0, s32 arg1);
void Ramp_Start(u8 *r, f32 a, f32 b, f32 c);
s32 Ramp_Step(u8 *r);
void func_00113A30(u8 *arg0, u8 *arg1);
void func_0029D548(void);
void func_00113548(u8 *arg0, f32 farg0);
void func_00113600(f32 farg0, f32 farg1);
void func_00113620(u8 *arg0, s32 arg1);
void func_0029D580(s32 arg0);
void func_00112B28(s32 arg0);
void HudNotice_GsBeginAdd();
void HudNotice_GsEndAdd();
void func_00113430(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

/* Fade/pulse state machine of a HUD notice; p[0] = state (0..5). */
s32 func_00119630(void) {
    u8 sp[0x190];
    u8 *A = sp;
    u8 *B = sp + 0x60;
    u8 *C = sp + 0xC0;
    u8 *tmp = sp + 0x180;
    u8 *p = (u8 *)(func_0010B078() + 0x78);
    s32 *pHud = (s32 *)func_0010B080();
    u8 *r1;
    u8 *r2;
    s32 hasR = 0;
    s32 flash = 0;
    f32 sA = 1.0f;
    f32 sB = 1.0f;
    f32 sC = 1.0f;
    u32 v;
    s32 w;
    f32 f;

    func_00113860(sp + 0xC, 0, 0, 0x80, 0x20, 8);
    func_00113D80(sp, 0);
    func_00113B00(sp, 0xC0, 0x3A);
    __builtin_memcpy(B, A, 0x60);
    func_00113BE0(sp + 0x120, 1);
    *(s32 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x38) = 0;

    switch (*(u32 *)p) {
    case 0:
        r1 = p + 4;
        r2 = p + 0x1C;
        Ramp_Start(r1, D_00384010, 0.0f, 1.0f);
        Ramp_Start(r2, D_00384014, 1.0f, 0.0f);
        *(s32 *)p = *(s32 *)p + 1;
        goto ramps;
    case 1:
        r1 = p + 4;
        r2 = p + 0x1C;
    ramps:
        hasR = 1;
        if (Ramp_Step(r1) != 0) {
            w = -0x80;
            sp[0x78] = (u8)w;
            sp[0x16] = (u8)w;
            sp[0x17] = (u8)w;
            sp[0x18] = (u8)w;
            sp[0x19] = (u8)w;
        } else {
            v = (u32)(*(f32 *)(p + 0x14) * 128.0f);
            w = 0xFF - (s32)v;
            sp[0x19] = (u8)v;
            sp[0x78] = (u8)w;
            sp[0x16] = (u8)w;
            sp[0x17] = (u8)w;
            sp[0x18] = (u8)w;
        }
        sp[0x76] = (u8)w;
        sp[0x77] = (u8)w;
        if (Ramp_Step(r2) != 0) {
            Ramp_Start(r1, 0.25f, 0.0f, 1.0f);
            *(s32 *)p = *(s32 *)p + 1;
            sp[0x79] = 0;
        } else {
            f = *(f32 *)(p + 0x2C);
            sB = (1.0f - f) + 1.0f;
            sC = sB;
            v = (u32)(f * 128.0f);
            sp[0x79] = (u8)v;
        }
        break;
    case 2:
        r1 = p + 4;
        if (Ramp_Step(r1) == 0) {
            flash = 1;
        } else {
            Ramp_Start(r1, D_00384018, 0.0f, 1.0f);
            *(s32 *)p = *(s32 *)p + 1;
        }
        break;
    case 3:
        r1 = p + 4;
        if (Ramp_Step(r1) != 0) {
            Ramp_Start(r1, 0.25f, 1.0f, 0.0f);
            *(s32 *)p = *(s32 *)p + 1;
        }
        break;
    case 4:
        if (Ramp_Step(p + 4) == 0) {
            f = *(f32 *)(p + 0x14);
            sA = (1.0f - f) * D_0038401C + 1.0f;
            v = (u32)(f * 128.0f);
            sp[0x19] = (u8)v;
        } else {
            sp[0x19] = 0;
            *(s32 *)p = *(s32 *)p + 1;
        }
        break;
    case 5:
        return 1;
    default:
        break;
    }

    if (hasR == 0) {
        *(s32 *)(B) = 0;
    }

    if (flash == 0) {
        *(s32 *)C = 0;
    } else {
        __builtin_memset(tmp, 0, 8);
        __builtin_memcpy(C, A, 0x60);
        *(s32 *)C = *(s32 *)C | 0x80;
        *(s16 *)(C + 0x12) = 0x40;
        *(s16 *)(C + 0x10) = 0x200;
        *(s16 *)(C + 0x14) = 7;
        *(s16 *)(C + 0xC) = 0;
        *(s16 *)(C + 0xE) = 0;
        *(s32 *)(tmp + 4) = 0;
        *(f32 *)tmp = *(f32 *)(p + 0x14);
        func_00113A30(C, tmp);
    }

    func_0029D548();
    func_00113548(p + 0x34, 0.0f);
    func_0029D548();
    func_00113600(sC, sB);
    func_00113620(B, 1);
    func_0029D580(1);
    func_00113600(sA, sA);
    func_00113620(sp, 1);
    func_00113620(C, 1);
    func_0029D580(1);
    func_00112B28(*pHud);
    if (flash != 0) {
        HudNotice_GsBeginAdd();
        func_00113430(*pHud, sp, 1, 0x2A00, 0x2C00, 0, 0);
        HudNotice_GsEndAdd();
    } else {
        func_00113430(*pHud, sp, 1, 0x2A00, 0x2C00, 0, 0);
    }
    return 0;
}
