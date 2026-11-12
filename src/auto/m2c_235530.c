#include "m2c_macros.h"

s32 func_00212320();                                /* extern */
s32 func_00241250(void *, s32);                     /* extern */

void func_00235530(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_00241250(arg0, func_00212320(arg0));
    M2C_FIELD(arg0, s32 *, 0x1510) = 0;
    M2C_FIELD(arg0, s32 *, 0xA34) = temp_v0;
}
