#include "common.h"

void Dma_SendVif1(s32 arg0);
extern u8 D_00387EB1;
extern u8 D_0038A628[] __attribute__((section(".data")));
extern s32 gDmaCur;

void func_0028B110(void) {
    s32 temp_p;
    u8 temp_v0_2;

    temp_p = gDmaCur;
    *(s64 *)temp_p = (s64)0xE000 << 47;
    gDmaCur = temp_p + 8;
    *(s64 *)(temp_p + 8) = 0;
    gDmaCur = temp_p + 16;
    Dma_SendVif1(*(s32 *)((s32)D_0038A628 + D_00387EB1 * 4 + 8));
    temp_v0_2 = D_00387EB1 ^ 1;
    D_00387EB1 = temp_v0_2;
    gDmaCur = *(s32 *)((s32)D_0038A628 + (temp_v0_2 & 0xFF) * 4 + 8);
}
