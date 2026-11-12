#include "common.h"

extern u8 D_00376CA0[];
void *memcpy(void *dst, const void *src, u32 n);
void Dma_AddData(void *arg0, s32 arg1);

void Ot_AddRestoreEnv(void) {
    u8 buf[0x90];

    memcpy(buf, D_00376CA0, 0x90);
    Dma_AddData(buf, 0x90);
}
