#include "m2c_macros.h"

M2C_UNK func_002F8F00(s32);                         /* extern */

void func_002E7F50(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 4) == 3) {
        func_002F8F00(M2C_FIELD(arg0, s32 *, 8));
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s32 *, 4) = 0;
    }
}
