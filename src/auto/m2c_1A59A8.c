#include "m2c_macros.h"

s32 func_001A5B18(void *);                          /* extern */
s32 func_001A5E48(void *);                          /* extern */

void func_001A59A8(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    if ((M2C_FIELD(arg0, u8 *, 1) == 1) && (func_001A5B18(temp_s0) == 0) && (func_001A5E48(temp_s0) == 0)) {
        M2C_FIELD(temp_s0, s16 *, 0x88) = 4;
    }
}
