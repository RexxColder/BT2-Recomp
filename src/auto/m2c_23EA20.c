#include "m2c_macros.h"

u32 func_0023E520();                                /* extern */

s32 Battle_GetSetup(void *arg0) {
    u32 temp_v0;

    temp_v0 = func_0023E520(arg0);
    if (temp_v0 >= 0x6AU) {
        return M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x974);
    }
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x974) + (temp_v0 * 0x64);
}
