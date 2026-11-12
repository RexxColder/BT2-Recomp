#include "m2c_macros.h"

extern void *gEftCam;

void func_00126E80(s8 arg0) {
    M2C_FIELD(gEftCam, s8 *, 0xE) = arg0;
}
