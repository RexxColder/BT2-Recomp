#include "m2c_macros.h"

M2C_UNK func_002FC638();                            /* extern */
M2C_UNK func_002FC670();                            /* extern */
M2C_UNK func_00331710(M2C_UNK *, s32);              /* extern */
s32 sceIoctl(s32, M2C_UNK, M2C_UNK);                /* extern */
extern M2C_UNK D_0037E0E0 __attribute__((section(".data")));

s32 func_002FC7E8(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_v0;

    func_002FC638();
    temp_v0 = sceIoctl(arg0, arg1, arg2);
    if (temp_v0 < 0) {
        func_00331710(&D_0037E0E0, temp_v0);
    }
    func_002FC670();
    return temp_v0;
}
