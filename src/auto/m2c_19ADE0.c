#include "m2c_macros.h"

s32 func_0019B0E8();                                /* extern */
s32 func_0019B308(void *);                          /* extern */

void func_0019ADE0(void *arg0) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    if ((M2C_FIELD(arg0, u8 *, 1) == 3) && (func_0019B0E8(arg0) == 0)) {
        if (func_0019B308(arg0) == 0) {
            M2C_FIELD(temp_s1, u16 *, 0x58) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x58) | 4);
        }
    }
}
