#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_00272C60(s32);                         /* extern */
s32 func_002ACA20(s32);                             /* extern */
extern s32 D_003B2678 __attribute__((section(".data")));

s32 func_002A7978(s32 arg0) {
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt();
        func_00272C60(temp_v0);
        D_003B2678 = func_002ACA20(temp_v0);
    }
    return 1;
}
