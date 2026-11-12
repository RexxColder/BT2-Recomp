#include "m2c_macros.h"

s32 func_002C2FF0();           /* extern */
s32 func_00304760();                   /* extern */

s32 func_002BFAD8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = arg2 - arg3;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = temp_v0;
    if (temp_v0 <= 0) {
        return func_002C2FF0(0, 0xFF00040C, arg3);
    }
    M2C_FIELD(arg0, s32 *, 0x10) = arg3;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    temp_v0_2 = func_00304760(arg1, temp_v0, arg3);
    M2C_FIELD(arg0, s32 *, 4) = temp_v0_2;
    if (temp_v0_2 == 0) {
        return func_002C2FF0(0, 0xFF00040A);
    }
    return 0;
}
