#include "m2c_macros.h"

void *BtlChar_GetPos();                             /* extern */

f32 func_00217330(void *arg0) {
    f32 temp_f20;

    temp_f20 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), f32 *, 0xE64);
    return temp_f20 - M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 4);
}
