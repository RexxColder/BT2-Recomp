#include "m2c_macros.h"

M2C_UNK func_002E7F08(s32);                         /* extern */

void func_002F0480(void *arg0) {
    func_002E7F08(M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(arg0, s8 *, 1) = 0;
}
