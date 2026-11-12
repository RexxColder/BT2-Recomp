#include "common.h"

void EftBurst_RelocateModel(s32 arg0);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern u8 gEftBurstRes[] __attribute__((section(".data")));

void func_00134688(void) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_s0 = *(s32 *)(D_003876A0 + 0x2C);
    temp_v0 = temp_s0 + ((*(u32 *)(temp_s0 + 4) >> 2) * 4);
    *(s32 *)(gEftBurstRes + 0xC) = temp_v0;
    EftBurst_RelocateModel(temp_v0);
    temp_v0_2 = temp_s0 + ((*(u32 *)(temp_s0 + 0xC) >> 2) * 4);
    *(s32 *)(gEftBurstRes + 4) = temp_v0_2;
    Res_RelocateOffsets((s32)(gEftBurstRes + 4), temp_v0_2, temp_v0_2);
    *(s32 *)(gEftBurstRes + 0x14) = 0;
    *(s32 *)(gEftBurstRes + 0x10) = 1;
    *(s32 *)(gEftBurstRes + 8) = temp_s0 + ((*(u32 *)(temp_s0 + 8) >> 2) * 4);
}
