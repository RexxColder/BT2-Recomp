#include "m2c_macros.h"

M2C_UNK func_002C2FF0(void *, M2C_UNK);             /* extern */
s32 func_002C3210();                                /* extern */
void *func_002CAB18(void *, M2C_UNK);               /* extern */

void func_002CA9D0(void *arg0, M2C_UNK arg1) {
    void *temp_v0;

    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(NULL, 0xFF000188);
        return;
    }
    temp_v0 = func_002CAB18(arg0, arg1);
    if (temp_v0 == NULL) {
        func_002C2FF0(arg0, 0xFF000F30);
    } else {
        M2C_FIELD(temp_v0, s32 *, 4) = (s32) (M2C_FIELD(temp_v0, s32 *, 4) + 1);
    }
    M2C_FIELD(arg0, s32 *, 0x980) = (s32) (M2C_FIELD(arg0, s32 *, 0x980) + 1);
}
