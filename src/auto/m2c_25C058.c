#include "m2c_macros.h"

M2C_UNK Dma_AddScissor(s32, s32, s32, s32);         /* extern */
M2C_UNK func_0025B650(void *);                      /* extern */
extern void *gBtlCam;

void func_0025C058(void) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(gBtlCam, void **, 0x600);
    Dma_AddScissor(M2C_FIELD(temp_s0, s32 *, 0x200), M2C_FIELD(temp_s0, s32 *, 0x204), M2C_FIELD(temp_s0, s32 *, 0x208), M2C_FIELD(temp_s0, s32 *, 0x20C));
    func_0025B650(temp_s0);
}
