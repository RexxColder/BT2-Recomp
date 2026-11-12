#include "m2c_macros.h"

M2C_UNK func_0025C6B8();                            /* extern */
s32 func_0028BAA8(M2C_UNK);                         /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 gOrbitCam;

void func_0025C740(void) {
    s32 temp_v0;

    temp_v0 = func_0028BAA8(0x290);
    gOrbitCam = temp_v0;
    memset(temp_v0, 0, 0x290);
    func_0025C6B8();
}
