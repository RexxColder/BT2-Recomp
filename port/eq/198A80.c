#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
void EftGlow_CalcFrame(void *arg0, s32 arg1, s32 arg2);
void func_00128900(void *arg0, void *arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
s32 func_00209C18(s32 arg0);
s32 rand();
extern f32 D_00384D30;
extern f32 D_00384D34;
extern f32 D_00384D38;
extern f32 D_00384D3C;
extern u8 *gEftGlowCfg;

void EftGlow_Begin(u8 *arg0, s32 *arg1) {
    s32 sp[16];
    f32 temp_f20;
    s32 var_s2;
    s32 var_s3;
    s32 var_s3_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    u8 *var_s0;
    u8 *var_s2_2;
    u8 *var_a0;

    var_s0 = arg0 + 0x1B0;
    var_s2 = 9;
    var_s3 = 0x490;
    *(s32 *)(arg0 + 0) = 1;
    temp_v0 = func_00209C18(*arg1);
    *(s32 *)(arg0 + 0x10) = 0;
    *(s32 *)(arg0 + 0xC) = temp_v0;
    *(s32 *)(arg0 + 0x4C) = *arg1;
    *(f32 *)(arg0 + 0x40) = D_00384D30;
    *(f32 *)(arg0 + 0x44) = D_00384D34;
    *(s32 *)(arg0 + 0x18) = 0;
    do {
        var_s2 -= 1;
        func_00208DE8(*arg1, var_s0, *(s32 *)(gEftGlowCfg + var_s3));
        var_s3 += 0x18;
        var_s0 += 0x10;
    } while (var_s2 >= 0);

    var_s3_2 = 4;
    temp_f20 = D_00384D38;
    temp_s0 = rand();
    var_s2_2 = arg0 + 0x150;
    *(f32 *)(arg0 + 0x250) = *(f32 *)(gEftGlowCfg + 0x1B0) * (((f32)temp_s0 / temp_f20) - ((f32)rand() / temp_f20));
    temp_s0_2 = rand();
    *(f32 *)(arg0 + 0x254) = *(f32 *)(gEftGlowCfg + 0x1B4) * (((f32)temp_s0_2 / temp_f20) - ((f32)rand() / temp_f20));
    *(f32 *)(arg0 + 0x258) = *(f32 *)(gEftGlowCfg + 0x1B8);
    EftGlow_CalcFrame(sp, *arg1, *(s32 *)(arg0 + 0xC));

    var_a0 = var_s2_2;
    do {
        var_s2_2 -= 0x40;
        var_s3_2 -= 1;
        func_00128900(var_a0, sp);
        var_a0 = var_s2_2;
    } while (var_s3_2 >= 0);

    *(s32 *)(arg0 + 0x34) = 1;
    *(s32 *)(arg0 + 0x3C) = 0;
    *(f32 *)(arg0 + 0x38) = *(f32 *)(gEftGlowCfg + 0x1A8);
    *(s32 *)(arg0 + 0x30) = 0;
    *(f32 *)(arg0 + 0x48) = BtlCharApi_GetHeight(*arg1) / D_00384D3C;
}
