#include "m2c_macros.h"

M2C_UNK func_001D8598(f32, s32);                    /* extern */
f32 func_00208670(s32);                             /* extern */

void func_001D45B8(void *arg0) {
    if (!(M2C_FIELD(arg0, s32 *, 4) & 3)) {
        func_001D8598(func_00208670(M2C_FIELD(arg0, s32 *, 0)), M2C_FIELD(arg0, s32 *, 0));
    }
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 1);
}
