#include "m2c_macros.h"

s32 func_00203C58(void *, M2C_UNK);                 /* extern */
M2C_UNK func_00203C88(void *, M2C_UNK);             /* extern */
M2C_UNK func_002113C0(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
s32 func_00212320();                                /* extern */
s32 func_00241250(void *, s32);                     /* extern */

void func_00236E70(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_00241250(arg0, func_00212320(arg0));
    M2C_FIELD(arg0, s32 *, 0x1510) = 0;
    M2C_FIELD(arg0, s32 *, 0xA34) = temp_v0;
    func_00203C88(arg0, 0x08000000);
    if (func_00203C58(arg0, 0x10000000) != 0) {
        func_002113C0(arg0, 0, 0x4000, 1);
    }
}
