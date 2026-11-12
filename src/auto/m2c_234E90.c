#include "m2c_macros.h"

s32 func_00211310();        /* extern */
s32 func_00212320();                          /* extern */
s32 func_002411E0();                     /* extern */
s32 func_00241250();                     /* extern */

void func_00234E90(void *arg0, s32 arg1) {
    void *temp_a0;
    void *temp_v1;

    M2C_FIELD(arg0, s32 *, 0xA34) = func_00241250(arg0, func_00212320(arg0));
    M2C_FIELD(arg0, s32 *, 0x1510) = 0;
    if (arg1 < 0xC4) {
        if (arg1 < 0xC1) {
            goto block_2;
        }
    } else {
block_2:
        if (func_002411E0(arg0, func_00212320(arg0)) & 0x20000) {
            if (func_00211310(arg0, 8, 1) == 0) {
                temp_v1 = M2C_FIELD(arg0, void **, 0x1530);
                M2C_FIELD(temp_v1, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xAF0) & 0xFF00FFFF);
                temp_a0 = M2C_FIELD(arg0, void **, 0x1530);
                M2C_FIELD(temp_a0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xAF0) | 0x10000);
            }
        }
    }
}
