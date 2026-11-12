#include "m2c_macros.h"

extern void *D_00387A30;

void DemoCam_Stop(void) {
    if (M2C_FIELD(D_00387A30, s32 *, 0x2B0) != 0) {
        M2C_FIELD(D_00387A30, s32 *, 0x2F8) = (s32) (M2C_FIELD(D_00387A30, s32 *, 0x2F8) | 2);
    }
}
