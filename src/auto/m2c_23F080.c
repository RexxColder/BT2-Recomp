#include "m2c_macros.h"

void *Battle_GetSetup();                            /* extern */
s32 func_001F9978(s32);                             /* extern */
extern f32 D_00386C94;
extern f32 D_00386C98;

f32 func_0023F080(s32 arg0) {
    f32 temp_f20;

    temp_f20 = M2C_FIELD(Battle_GetSetup(arg0), f32 *, 0x38) * 10.0f * D_00386C94;
    return temp_f20 * ((f32) func_001F9978(arg0) * D_00386C98);
}
