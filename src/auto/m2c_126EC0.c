#include "m2c_macros.h"

extern void *gEftCam;

s32  func_00126EC0(void) {
    return (u8)(M2C_FIELD(gEftCam, u8 *, 0xC));
}
