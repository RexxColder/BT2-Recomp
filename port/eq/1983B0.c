#include "common.h"

f32 EftGlow_CalcLength(u8 *arg0, s32 arg1);
f32 EftGlow_CalcWidth(u8 *arg0, s32 arg1, s32 arg2);
void func_00129C28(u8 *arg0, u8 *arg1);
s32 rand(void);
extern f32 *gEftGlowCfg2;

void EftGlow_PairPart(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 hi;
    u8 a2b;
    u8 *v0;
    f32 f0;
    f32 f4;
    f32 f4b;

    hi = rand() % *(s32 *)(arg0 + 0x24);
    a2b = *(u8 *)(arg2 + 9);
    *(u8 *)(arg1 + 9) = a2b;
    *(u8 *)(arg1 + 0xE) = *(u8 *)(arg2 + 0xE);
    *(f32 *)(arg1 + 0x10) = *(f32 *)(arg2 + 0x10) * 1.5f;
    *(f32 *)(arg1 + 0x14) = *(f32 *)(arg2 + 0x14) * 1.5f;
    f0 = EftGlow_CalcWidth(arg1, 1, a2b);
    *(f32 *)(arg1 + 0x2C) = (f0 - *(f32 *)(arg1 + 0x1C)) / (*(f32 *)(arg1 + 0x10) * *gEftGlowCfg2);
    f0 = EftGlow_CalcLength(arg1, 1);
    *(f32 *)(arg1 + 0x30) = (f0 - *(f32 *)(arg1 + 0x20)) / (*(f32 *)(arg1 + 0x10) * *gEftGlowCfg2);
    *(f32 *)(arg1 + 0x34) = *(f32 *)(arg2 + 0x34);
    *(f32 *)(arg1 + 0x3C) = *(f32 *)(arg2 + 0x3C);
    func_00129C28(arg1 + 0x90, arg2 + 0x90);
    func_00129C28(arg1 + 0x70, arg2 + 0x70);
    v0 = arg0 + (hi * 0x10 + 0x260);
    f4 = *(f32 *)(arg0 + 0x48) * 4.0f;
    *(f32 *)(arg1 + 0x70) = *(f32 *)(arg1 + 0x70) - *(f32 *)(arg1 + 0x90) * f4;
    *(f32 *)(arg1 + 0x74) = *(f32 *)(arg1 + 0x74) - *(f32 *)(arg1 + 0x94) * f4;
    *(f32 *)(arg1 + 0x78) = *(f32 *)(arg1 + 0x78) - *(f32 *)(arg1 + 0x98) * f4;
    f4b = *(f32 *)(arg1 + 0x14);
    *(f32 *)(arg1 + 0x60) = (*(f32 *)v0 - *(f32 *)(arg1 + 0x50)) / f4b;
    *(f32 *)(arg1 + 0x64) = (*(f32 *)(v0 + 4) - *(f32 *)(arg1 + 0x54)) / f4b;
    *(f32 *)(arg1 + 0x68) = (*(f32 *)(v0 + 8) - *(f32 *)(arg1 + 0x58)) / f4b;
}
