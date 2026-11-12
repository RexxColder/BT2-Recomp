#include "m2c_macros.h"

M2C_UNK func_00208860();                            /* extern */
f32 func_00208DC0(s32);                             /* extern */

void func_001EEEB0(s32 arg0, void *arg1) {
    func_00208860(arg0, arg1);
    M2C_FIELD(arg1, f32 *, 4) = func_00208DC0(arg0);
}
