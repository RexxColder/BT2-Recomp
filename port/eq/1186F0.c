#include "common.h"

extern f32 D_00383FA0;
extern f32 D_00383FA4;
extern f32 D_00383FA8;
extern f32 D_00383FAC;
extern f32 D_00383FB0;
extern f32 D_00383FB4;
extern f32 D_00383FB8;

s32 func_0010B078(void);
s32 func_0010B080(void);
void func_00113860(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113D80(u8 *arg0, s32 arg1);
void func_00113BE0(u8 *arg0, s32 arg1);
void func_00113A30(u8 *arg0, u8 *arg1);
void func_0029D548(void);
void func_00113548(u8 *arg0, f32 farg0);
void func_00113600(f32 farg0, f32 farg1);
void func_00113620(u8 *arg0, s32 arg1);
void func_0029D580(s32 arg0);
void func_00112B28(s32 arg0);
void func_00113430(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void HudNotice_GsBeginAdd();
extern void HudNotice_GsEndAdd();
extern s32 Ramp_Step(u8 *arg0);
extern void Ramp_Start(u8 *arg0, f32 farg0, f32 farg1, f32 farg2);

/* HUD notice fade sequence (6 states in st[0]): ramps at st+4 and st+0x1C drive the alpha / scale. Returns 1 when done. */
s32 func_001186F0(void) {
    u8 *st = (u8 *)func_0010B078();
    s32 *gs = (s32 *)func_0010B080();
    u8 hud[0x60];
    u8 hud2[0x60];
    u8 unused[0x60];
    u8 tmp[8];
    f32 scaleX = 1.0f; /* f22 */
    f32 scaleY = 1.0f; /* f23 */
    f32 offs = 0.0f;
    f32 t;

    func_00113860(hud + 0xC, 0, 0x40, 0x200, 0x80, 4);
    func_00113D80(hud, 1);
    *(s16 *)(hud + 6) = 0xC0;
    *(s16 *)(hud + 0xA) = 0x100;
    func_00113BE0(unused, 1);
    switch (*(u32 *)st) {
    case 0:
        Ramp_Start(st + 4, D_00383FA0, 0.0f, 1.0f);
        Ramp_Start(st + 0x1C, D_00383FA4, 0.0f, 1.0f);
        *(f32 *)(st + 0x34) = 0.0f;
        *(f32 *)(st + 0x38) = 0.0f;
        *(s32 *)st += 1;
        /* fall through */
    case 1:
        Ramp_Step(st + 4);
        hud[0x19] = 0x80;
        if (Ramp_Step(st + 0x1C) == 0) {
            t = 1.0f - *(f32 *)(st + 0x2C);
            offs = t * D_00383FAC;
            scaleX = t * 3.0f + 1.0f;
            scaleY = scaleX;
        } else {
            Ramp_Start(st + 0x1C, D_00383FA8, 0.0f, 1.0f);
            *(s32 *)st += 1;
        }
        break;
    case 2:
        if (Ramp_Step(st + 0x1C) != 0) {
            Ramp_Start(st + 0x1C, D_00383FB0, 1.0f, 0.0f);
            *(s32 *)st += 1;
        }
        break;
    case 3:
        if (Ramp_Step(st + 0x1C) != 0) {
            Ramp_Start(st + 4, D_00383FB4, 1.0f, 0.0f);
            *(s32 *)st += 1;
        }
        break;
    case 4:
        if (Ramp_Step(st + 4) != 0) {
            hud[0x19] = 0;
            *(s32 *)st += 1;
        } else {
            t = *(f32 *)(st + 0x14) * 128.0f;
            if (t >= 2147483648.0f) {
                hud[0x19] = (u8)((s32)(t - 2147483648.0f) | 0x80000000);
            } else {
                hud[0x19] = (u8)(s32)t;
            }
            scaleX = (1.0f - *(f32 *)(st + 0x14)) * D_00383FB8 + 1.0f;
        }
        break;
    case 5:
        return 1;
    default:
        break;
    }
    __builtin_memcpy(hud2, hud, 0x60);
    *(u32 *)hud2 |= 0x80;
    *(s16 *)(hud2 + 0x12) = 0x40;
    *(s16 *)(hud2 + 0x14) = 7;
    *(s16 *)(hud2 + 0xE) = 0;
    if (*(s32 *)st == 2) {
        __builtin_memset(tmp, 0, 8);
        *(s32 *)(tmp + 4) = 0;
        *(f32 *)tmp = *(f32 *)(st + 0x2C);
        func_00113A30(hud2, tmp);
    }
    func_0029D548();
    func_00113548(st + 0x34, offs);
    func_00113600(scaleY, scaleX);
    func_00113620(hud, 1);
    func_00113620(hud2, 1);
    func_0029D580(1);
    HudNotice_GsBeginAdd();
    func_00112B28(*gs);
    func_00113430(*gs, hud, 1, 0x2A00, 0x2C00, 0, 0);
    HudNotice_GsEndAdd();
    return 0;
}
