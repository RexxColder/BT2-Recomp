#include "m2c_macros.h"

s32 func_001F9978(s32);                             /* extern */
void *func_0023EA80();                              /* extern */
extern f32 D_00386C9C;
extern f32 D_00386CA0;

f32 func_0023F0E0(s32 arg0) {
    f32 temp_f20;

    temp_f20 = M2C_FIELD(func_0023EA80(arg0), f32 *, 0x38) * 10.0f * D_00386C9C;
    return temp_f20 * ((f32) func_001F9978(arg0) * D_00386CA0);
}
