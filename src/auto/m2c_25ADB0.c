#include "m2c_macros.h"

extern void *D_00387A30;

void DemoCam_SetScaleHeight(s8 arg0) {
    M2C_FIELD(D_00387A30, s8 *, 0x31D) = arg0;
}
