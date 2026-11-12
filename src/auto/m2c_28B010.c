#include "m2c_macros.h"

M2C_UNK memcpy(s32, s32, u32);                      /* extern */
extern s32 gDmaCur;

void Dma_AddData(s32 arg0, u32 arg1) {
    memcpy(gDmaCur, arg0, arg1);
    gDmaCur += (arg1 >> 3) * 8;
}
