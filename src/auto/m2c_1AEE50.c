#include "m2c_macros.h"

s32 func_001267E8(s32, M2C_UNK);                    /* extern */
M2C_UNK func_001AF250(void *);                      /* extern */

void func_001AEE50(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    if (func_001267E8(M2C_FIELD(temp_s0, s32 *, 0x44), 0) == 0) {
        func_001AF250(temp_s0);
    }
}
