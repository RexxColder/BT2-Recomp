#include "m2c_macros.h"

s32 func_002411A0(s32 arg0, s32 arg1);              /* extern */

s32 func_002411E0(void *arg0, s32 arg1) {
    return M2C_FIELD(((func_002411A0((s32)arg0, arg1) * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x980)), s32 *, 0xD0);
}
