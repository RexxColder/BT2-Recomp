#include "m2c_macros.h"

s32 func_0019BDF0();                                /* extern */
s32 func_0019C0C0(void *);                          /* extern */

void func_0019BA88(void *arg0) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    if ((M2C_FIELD(arg0, u8 *, 1) == 3) && (func_0019BDF0(arg0) == 0)) {
        if (func_0019C0C0(arg0) == 0) {
            M2C_FIELD(temp_s1, u16 *, 0x88) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x88) | 4);
        }
    }
}
