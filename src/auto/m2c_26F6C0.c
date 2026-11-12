#include "m2c_macros.h"

s32 func_0026FFA0(s32);                             /* extern */
s32 func_0028BAA8(s32);                             /* extern */
M2C_UNK memset(s32, M2C_UNK, s32);                  /* extern */

s32 func_0026F6C0(void *arg0, void *arg1) {
    s32 temp_s0;
    s32 temp_s1_2;
    s32 temp_v0;
    u16 temp_s1;

    temp_s1 = M2C_FIELD(M2C_FIELD(arg1, void **, 0x18), u16 *, 0x12);
    temp_s1_2 = temp_s1 + func_0026FFA0(M2C_FIELD(arg1, s32 *, 0x1C));
    temp_s0 = temp_s1_2 * 0x38;
    temp_v0 = func_0028BAA8(temp_s0);
    M2C_FIELD(arg0, s32 *, 0) = temp_v0;
    memset(temp_v0, 0, temp_s0);
    M2C_FIELD(arg0, s32 *, 4) = temp_s1_2;
    return temp_s0;
}
