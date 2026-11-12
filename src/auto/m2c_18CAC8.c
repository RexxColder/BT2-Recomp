#include "m2c_macros.h"

s32 func_001267E8(s32, u8);                         /* extern */
M2C_UNK func_0018D4F0(void *, s32, s32);            /* extern */

void func_0018CAC8(void *arg0) {
    void *temp_s0;
    void *temp_s1;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    temp_s1 = M2C_FIELD(temp_s0, void **, 4);
    if ((M2C_FIELD(temp_s0, s32 *, 0) != 0) && (func_001267E8(M2C_FIELD(temp_s0, s32 *, 0x50), M2C_FIELD(temp_s0, u8 *, 0x54)) == 0)) {
        func_0018D4F0(temp_s0, M2C_FIELD(temp_s1, s32 *, 0x9C), M2C_FIELD(temp_s1, s32 *, 0xAC));
    }
}
