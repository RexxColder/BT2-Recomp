#include "m2c_macros.h"

s32 func_002C2FF0(M2C_UNK, M2C_UNK);                /* extern */

s32 func_002CDFD8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 4) == 0) {
        return func_002C2FF0(0, 0xFF000204);
    }
    if ((u32) M2C_FIELD(arg0, u32 *, 0x40) < 0x37D0U) {
        return func_002C2FF0(0, 0xFF000205);
    }
    return 0;
}
