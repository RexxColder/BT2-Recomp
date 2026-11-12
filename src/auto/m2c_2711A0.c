#include "m2c_macros.h"

M2C_UNK func_002712B0(s32, M2C_UNK);                /* extern */
M2C_UNK func_0028C778();                            /* extern */
M2C_UNK sceGsSwapDBuff(M2C_UNK *, s32);             /* extern */
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);            /* extern */
extern M2C_UNK gGfx __attribute__((section(".data")));

void func_002711A0(void) {
    func_0028C778();
    sceGsSwapDBuff(&gGfx, M2C_FIELD(&gGfx, s32 *, 0x234));
    func_002712B0(M2C_FIELD(&gGfx, s32 *, 0x230), 1);
    sceGsSyncPath(0, 0);
}
