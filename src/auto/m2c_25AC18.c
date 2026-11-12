#include "m2c_macros.h"

extern void *D_00387A30;

void DemoCam_StartAutoOnce(void) {
    if (M2C_FIELD(D_00387A30, s32 *, 0x2B0) != 0) {
        M2C_FIELD(D_00387A30, s8 *, 0x31C) = 0;
        M2C_FIELD(D_00387A30, s32 *, 0x2F8) = 0xD;
    }
}
