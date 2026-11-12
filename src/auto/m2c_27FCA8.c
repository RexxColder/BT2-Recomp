#include "m2c_macros.h"

M2C_UNK Dma_AddData(s32, M2C_UNK);                  /* extern */
M2C_UNK Dma_AddFrame(M2C_UNK, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Dma_AddZbuf(M2C_UNK, M2C_UNK);              /* extern */
M2C_UNK func_00271370();                            /* extern */
M2C_UNK func_002814D0(M2C_UNK, M2C_UNK, u16, M2C_UNK); /* extern */
extern s32 D_003B0A84 __attribute__((section(".data")));

void func_0027FCA8(void *arg0) {
    Dma_AddData(arg0 + 0xB94, 0x10);
    func_00271370();
    Dma_AddFrame((D_003B0A84 & 1) ? 0 : 0x70, 8, 0xFFFFFF);
    Dma_AddZbuf(0xE0, 1);
    func_002814D0(0, 0x1C00, M2C_FIELD(arg0, u16 *, 0xBB4), 0x44);
    Dma_AddZbuf(0xE0, 0);
}
