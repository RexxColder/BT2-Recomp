#include "m2c_macros.h"

M2C_UNK strncat(M2C_UNK *, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK strncpy(M2C_UNK *, s32, M2C_UNK);           /* extern */
extern M2C_UNK D_003664A8 __attribute__((section(".data")));
extern M2C_UNK D_003A0370 __attribute__((section(".data")));

void func_00307148(s32 arg0, M2C_UNK arg1) {
    strncpy(&D_003664A8, arg0, 0x7F);
    strncat(&D_003664A8, arg1, 0x7F);
    if (M2C_FIELD(&D_003A0370, M2C_UNK (**)(s32, M2C_UNK *), 0) != NULL) {
        M2C_FIELD(&D_003A0370, M2C_UNK (**)(s32, M2C_UNK *), 0)(M2C_FIELD(&D_003A0370, s32 *, 4), &D_003664A8);
    }
}
