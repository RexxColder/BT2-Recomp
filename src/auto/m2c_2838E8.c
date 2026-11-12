#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK gGfxLens __attribute__((section(".data")));

void GfxLens_Clear(void) {
    memset(&gGfxLens, 0, 0x180);
}
