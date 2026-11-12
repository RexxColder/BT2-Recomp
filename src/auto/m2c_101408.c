#include "m2c_macros.h"

s32 func_001013B0();                                /* extern */
M2C_UNK func_002F52A8(s32, s32);                    /* extern */
extern s32 gStgPanBlur;

void func_00101408(void) {
    s32 temp_s0;

    temp_s0 = gStgPanBlur;
    func_002F52A8(temp_s0, func_001013B0());
}
