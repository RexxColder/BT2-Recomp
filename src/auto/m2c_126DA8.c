#include "m2c_macros.h"

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 gEftCam;

void func_00126DA8(void) {
    if (gEftCam != 0) {
        memset(gEftCam, 0, 0x14);
    }
}
