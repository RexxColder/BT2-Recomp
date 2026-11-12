#include "common.h"

s32 rand(void);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_00129B58(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void func_00129BB8(f32 farg0, s32 arg1, s32 arg2);
void BtlCharApi_GetFrameMove(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg1, s32 arg2, f32 farg0);
void sceVu0ClampVector(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00384CCC;
extern u8 *gEftGlowCfg2;

void func_00197680(u8 *arg0, s32 arg1) {
    u8 buf[0x40];
    u8 *s1;
    s32 r;
    f32 f20;

    r = rand();
    f20 = *(f32 *)(gEftGlowCfg2 + 0xC) + *(f32 *)(gEftGlowCfg2 + 0x10) * ((f32)r / D_00384CCC);
    func_00208DE8(arg1, (s32)buf, 0x30);
    *(s32 *)(buf + 0xC) = 0;
    func_00208DE8(arg1, (s32)(buf + 0x10), 3);
    s1 = buf + 0x20;
    *(s32 *)(buf + 0x1C) = 0;
    func_00129B58((s32)s1, (s32)(buf + 0x10), (s32)buf);
    Vec3_Normalize((s32)s1, (s32)s1);
    func_00129BB8(f20, (s32)s1, (s32)s1);
    BtlCharApi_GetFrameMove(arg1, (s32)arg0);
    func_00129BD0((s32)arg0, (s32)arg0, *(f32 *)(gEftGlowCfg2 + 0x14));
    sceVu0ClampVector((s32)arg0, (s32)arg0, -0.5f, 0.5f);
    func_00129B28((s32)arg0, (s32)arg0, (s32)s1);
    *(s32 *)(arg0 + 0xC) = 0;
}
