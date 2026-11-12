#include "m2c_macros.h"

s32 func_001267E8(s32, u8);                         /* extern */
M2C_UNK func_001E9B80(void *);                      /* extern */

void func_001E9548(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    if (func_001267E8(M2C_FIELD(temp_s0, s32 *, 0x120), M2C_FIELD(temp_s0, u8 *, 0x126)) == 0) {
        func_001E9B80(temp_s0);
    }
}
