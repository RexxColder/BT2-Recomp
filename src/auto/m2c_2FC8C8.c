#include "m2c_macros.h"

M2C_UNK func_002FC638();                            /* extern */
M2C_UNK func_002FC670();                            /* extern */
M2C_UNK func_00331710(M2C_UNK *, s32);              /* extern */
s32 sceClose(s32);                                  /* extern */
extern M2C_UNK D_0037E120 __attribute__((section(".data")));

s32 func_002FC8C8(s32 arg0) {
    s32 temp_v0;

    func_002FC638();
    temp_v0 = sceClose(arg0);
    if (temp_v0 < 0) {
        func_00331710(&D_0037E120, temp_v0);
    }
    func_002FC670();
    return temp_v0;
}
