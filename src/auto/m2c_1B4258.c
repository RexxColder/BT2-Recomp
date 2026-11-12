#include "m2c_macros.h"

M2C_UNK EftTexSet_Keep32(s32, M2C_UNK, M2C_UNK);    /* extern */
extern s32 gEftRay;

void EftRay_StepTexture(void) {
    EftTexSet_Keep32(gEftRay, 1, 0);
}
