#include "m2c_macros.h"

M2C_UNK func_0025B5E8(s32, s32);                    /* extern */
M2C_UNK func_0025C798();                            /* extern */
extern s32 gOrbitCam;

void func_0025CBC8(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    func_0025C798(r_a0);
    func_0025B5E8(gOrbitCam + 0x30, gOrbitCam + 0x280);
}
