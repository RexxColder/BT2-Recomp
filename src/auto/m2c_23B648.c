#include "m2c_macros.h"

s32 func_00211310(void *, M2C_UNK, M2C_UNK);        /* extern */
s32 func_00212320();                                /* extern */
s32 func_00241C50(void *, s32);                     /* extern */

void func_0023B648(void *arg0) {
    s32 temp_v0;
    void *temp_a0;
    void *temp_v1;

    temp_v0 = func_00241C50(arg0, func_00212320(arg0));
    if (temp_v0 < 0x18) {
        if (temp_v0 >= 0x16) {
            if (func_00211310(arg0, 8, 1) == 0) {
                temp_v1 = M2C_FIELD(arg0, void **, 0x1530);
                M2C_FIELD(temp_v1, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xAF0) & 0xFF00FFFF);
                temp_a0 = M2C_FIELD(arg0, void **, 0x1530);
                M2C_FIELD(temp_a0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xAF0) | 0x10000);
            }
        }
    }
}
