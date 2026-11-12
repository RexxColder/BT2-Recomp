#include "m2c_macros.h"

void *func_002B61E0();                              /* extern */

void func_002B4BE8(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_002B61E0();
    M2C_FIELD(temp_v0, M2C_UNK (**)(s32, s32), 0x28)(M2C_FIELD(temp_v0, s32 *, 0x30), arg0);
}
