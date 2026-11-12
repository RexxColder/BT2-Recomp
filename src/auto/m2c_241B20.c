#include "m2c_macros.h"

s32 func_002411A0();                                /* extern */

f32 func_00241B20(void *arg0) {
    return M2C_FIELD(((func_002411A0(arg0) * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x980)), f32 *, 0xF4);
}
