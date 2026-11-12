#include "m2c_macros.h"

M2C_UNK DemoCam_Stop();                       /* extern */
s32 func_00211310(void *, s32, s32);        /* extern */
M2C_UNK func_0025AE48();                         /* extern */
M2C_UNK func_0025AEB8();                         /* extern */
M2C_UNK func_0025AF28();                         /* extern */

void func_001FBEB0(void *arg0) {
    if (func_00211310(arg0, 0xE, 1) != 0) {
        DemoCam_Stop();
    }
    if (func_00211310(arg0, 0xE, 2) != 0) {
        func_0025AE48(M2C_FIELD(arg0, s32 *, 0x1534));
    }
    if (func_00211310(arg0, 0xE, 4) != 0) {
        func_0025AEB8(M2C_FIELD(arg0, s32 *, 0x1534));
    }
    if (func_00211310(arg0, 0xE, 8) != 0) {
        func_0025AF28(M2C_FIELD(arg0, s32 *, 0x1534));
    }
}
