#include "m2c_macros.h"

extern s32 Dma_SendVif1(s32 arg0);
extern u8 D_00387EB0;
extern u32 D_0038A628[] __attribute__((section(".data")));
extern void *gDmaCur;

void func_0028B090(void) {
    u8 *p;

    p = (u8 *)gDmaCur;
    *(s64 *)p = (s64)0xE000 << 47;
    gDmaCur = p + 8;
    *(s64 *)(p + 8) = 0;
    gDmaCur = p + 16;
    Dma_SendVif1((s32)D_0038A628[D_00387EB0]);
    D_00387EB0 = D_00387EB0 ^ 1;
    gDmaCur = (void *)D_0038A628[D_00387EB0];
}
