#include "m2c_macros.h"

void *Battle_GetSetup();                            /* extern */
s32 func_001F98D0(s32);                             /* extern */

s32 func_0023ED70(s32 arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(Battle_GetSetup(arg0), s32 *, 0xC);
    return (s32) (temp_s0 * func_001F98D0(arg0)) / 100;
}
