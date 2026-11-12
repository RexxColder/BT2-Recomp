#include "m2c_macros.h"

s32 func_002411A0();                                /* extern */
extern f32 D_00386D24;

f32 func_00241B90(void *arg0) {
    return M2C_FIELD(((func_002411A0(arg0) * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x980)), f32 *, 0x10C) * 10.0f * D_00386D24;
}
