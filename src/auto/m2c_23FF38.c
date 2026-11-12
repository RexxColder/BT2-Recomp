#include "m2c_macros.h"

s32 func_0023FDB8();                                /* extern */

s32 BtlKiBlast_Get(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_0023FDB8(arg0);
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x978) + (((temp_v0 < 0) ? 0 : temp_v0) * 0x38);
}
