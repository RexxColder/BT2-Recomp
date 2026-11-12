#include "m2c_macros.h"

s32 func_002BE498();                             /* extern */
M2C_UNK func_002C0E10();           /* extern */
s32 func_002C0E40();                        /* extern */

void func_002BE3F0(s32 arg0) {
    s32 temp_s0;
    s32 temp_s2;
    void *temp_v0;

    temp_v0 = arg0 + 0x1FFC;
    temp_s2 = M2C_FIELD(temp_v0, s32 *, 0x14);
    temp_s0 = M2C_FIELD(temp_v0, s32 *, 0x10);
    if ((func_002C0E40(arg0, temp_s2) != 1) && (func_002C0E40(arg0, temp_s0) == 1) && (func_002BE498(arg0) != 0)) {
        func_002C0E10(arg0, temp_s2, 1);
    }
}
