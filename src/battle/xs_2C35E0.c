#include "m2c_macros.h"

s32 func_002D07B0(void *, s32);               /* extern */
M2C_UNK func_002DA838();               /* extern */

void func_002C35E0(void *arg0) {
    s32 temp_s1;
    s32 temp_s2;

    temp_s2 = *M2C_FIELD(arg0, s32 **, 0x1F7C);
    temp_s1 = func_002D07B0(arg0, 0x55);
    func_002DA838(temp_s2, temp_s1, func_002D07B0(arg0, 0x56));
}
