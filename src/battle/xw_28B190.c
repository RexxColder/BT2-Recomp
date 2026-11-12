#include "common.h"

extern s32 gDmaCur;

// Dma buffer bump allocator: rounds the size down to a multiple of 8, advances gDmaCur, returns the old pointer.
s32 Dma_Alloc(s32 arg0) {
    s32 old = gDmaCur;
    gDmaCur = old + (((u32)arg0 >> 3) << 3);
    return old;
}
