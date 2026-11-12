#include "common.h"

void FlushCache(s32 arg0, void *arg1, s32 arg2);
extern u8 *gDmaCur;

void Dma_EndDirect(u8 *arg0) {
    s32 temp_v0;

    temp_v0 = ((s32)(arg0 - gDmaCur) >> 4) - 1;
    *(s32 *)(gDmaCur + 0x8) = 0x10000000;
    *(s32 *)(gDmaCur + 0xC) = temp_v0 | 0x50000000;
    *(s32 *)(gDmaCur + 0x0) = temp_v0 | 0x10000000;
    FlushCache(0, gDmaCur, 0x10000000);
    gDmaCur = arg0;
}
