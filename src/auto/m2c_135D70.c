#include "m2c_macros.h"

M2C_UNK func_0028BB60(s32);                         /* extern */
extern s32 gEftBurst;

void GfxWater_Term(void) {
    if (gEftBurst != 0) {
        func_0028BB60(gEftBurst);
        gEftBurst = 0;
    }
}
