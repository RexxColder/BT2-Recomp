#include "m2c_macros.h"

M2C_UNK func_001EDC20(s32, M2C_UNK);                /* extern */
M2C_UNK func_0025E0B8(s32, s32, void *);            /* extern */
M2C_UNK func_00261558(s32, M2C_UNK);                /* extern */
s32 func_002623D8();                                /* extern */
M2C_UNK memset(void *, s32, s32);
extern void *D_00387A40;

// Zeroes 0x30 bytes at arg0, stores arg1 at +0x24, allocates a slot via func_002623D8 and sets it up (func_0025E0B8, func_00261558, func_001EDC20); returns slot or -1.
s32 func_001EDB20(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v0;

    memset(arg0, 0, 0x30);
    M2C_FIELD(arg0, s32 *, 0x24) = arg1;
    temp_v0 = func_002623D8();
    var_v0 = -1;
    if (temp_v0 >= 0) {
        func_0025E0B8(temp_v0, M2C_FIELD(D_00387A40, s32 *, 8) + (temp_v0 * 0x1520), arg0);
        func_00261558(temp_v0 & 0xFFFF, 0);
        func_001EDC20(temp_v0, 0);
        var_v0 = temp_v0;
    }
    return var_v0;
}
