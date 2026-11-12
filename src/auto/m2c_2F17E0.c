#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_00353F70 __attribute__((section(".data")));
extern M2C_UNK D_00353F90 __attribute__((section(".data")));

s32 func_002F17E0(void) {
    s32 temp_v1;

    temp_v1 = D_00353F70 + 1;
    D_00353F70 = temp_v1;
    if (temp_v1 == 1) {
        memset(&D_00353F90, 0, 0xF00);
    }
    return 1;
}
