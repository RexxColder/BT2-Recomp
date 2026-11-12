#include "m2c_macros.h"

M2C_UNK Dma_AddData(s32, M2C_UNK);                  /* extern */
M2C_UNK Dma_AddScissor(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK Dma_AddZbuf(M2C_UNK, M2C_UNK);              /* extern */
M2C_UNK func_00271370();                            /* extern */
M2C_UNK func_002814D0(M2C_UNK, M2C_UNK, u16, M2C_UNK); /* extern */

void func_00284818(void *arg0) {
    Dma_AddData(arg0 + 0x494, 0x10);
    func_00271370();
    Dma_AddZbuf(0xE0, 1);
    Dma_AddScissor(0, 0x1FF, 0, 0x1BF);
    func_002814D0(0, 0x1C00, M2C_FIELD(arg0, u16 *, 0x4B4), 0x44);
    Dma_AddZbuf(0xE0, 0);
}
