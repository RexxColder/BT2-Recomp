#include "m2c_macros.h"

M2C_UNK func_002BC790(void *);                      /* extern */
s32 func_002BC9A8();                                /* extern */
s32 func_002D0468(s32);                             /* extern */

void func_002BC710(void *arg0) {
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;

    temp_s1 = M2C_FIELD(arg0, s32 *, 0x1AC);
    temp_s2 = M2C_FIELD(arg0, s32 *, 0x3C);
    if ((temp_s1 == 1) && (func_002BC9A8(arg0) == temp_s1)) {
        M2C_FIELD(arg0, s32 *, 0x1AC) = 0;
    }
    func_002BC790(arg0);
    temp_v0 = func_002D0468(temp_s2);
    if ((temp_v0 == 4) || (temp_v0 == 6)) {
        M2C_FIELD(arg0, s32 *, 4) = 2;
    }
}
