#include "m2c_macros.h"

void *func_002B61E0();                              /* extern */

void func_002BD250(void *arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_002B61E0();
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 0x5C) = arg1;
    }
    M2C_FIELD(temp_v0, s32 *, 0x24) = arg1;
}
