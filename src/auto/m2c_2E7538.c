#include "m2c_macros.h"

M2C_UNK func_002F8DE0(s32);                         /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_002E7538(void *arg0) {
    s32 temp_a0;

    if (arg0 != NULL) {
        temp_a0 = M2C_FIELD(arg0, s32 *, 8);
        M2C_FIELD(arg0, s32 *, 8) = 0;
        func_002F8DE0(temp_a0);
        memset(arg0, 0, 0x104);
        M2C_FIELD(arg0, s16 *, 0) = 0;
    }
}
