#include "m2c_macros.h"

extern s32 gDmaCur;

// Appends a 16-byte DMA ref tag at gDmaCur: tag word (arg1>>4)+0x30000000, arg0, then two zero words; advances gDmaCur by 16.
void Dma_AddRef(s32 arg0, u32 arg1) {
    s32 *p;

    p = (s32 *) gDmaCur;
    p[0] = (s32) ((arg1 >> 4) + 0x30000000);
    p++;
    p[0] = arg0;
    p++;
    p[0] = 0;
    p[1] = 0;
    gDmaCur += 0x10;
}
