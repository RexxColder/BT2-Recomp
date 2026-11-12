#include "m2c_macros.h"

s32 BtlStage_IsReady();                             /* extern */
M2C_UNK Dma_AddScissor(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK ObjGs_AddDefaultEnv();                      /* extern */
s32 func_00276D80();                                /* extern */
extern void *D_00387A44;

void func_00269948(void) {
    if (BtlStage_IsReady() != 0) {
        if (func_00276D80() != 1) {
            Dma_AddScissor(0, 0x1FF, 0, 0x1BF);
            ObjGs_AddDefaultEnv();
            M2C_FIELD(D_00387A44, u8 *, 0xE550) = (u8) (M2C_FIELD(D_00387A44, u8 *, 0xE550) ^ 1);
        }
    }
}
