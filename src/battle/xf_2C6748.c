#include "m2c_macros.h"

s32 func_002C0670(void *, s32);                     /* extern */
s32 func_002C0EE0(void *, s32);                     /* extern */
s32 func_002C2FF0(void *, M2C_UNK);                 /* extern */

s32 func_002C6748(void *arg0) {
    s32 temp_s1;
    s32 temp_s2;

    temp_s2 = M2C_FIELD(arg0, s32 *, 0x1FC8);
    temp_s1 = func_002C0670(arg0, temp_s2);
    if ((temp_s1 - func_002C0EE0(arg0, temp_s2)) < M2C_FIELD(arg0, s32 *, 0x28)) {
        return func_002C2FF0(arg0, 0xFF000F1C);
    }
    return 0;
}
