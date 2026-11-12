#include "m2c_macros.h"

M2C_UNK func_00308428(s32, s32);                    /* extern */
M2C_UNK func_00308610(s32, s32);                         /* extern */

void func_002F03E0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x38) = arg1;
    func_00308610(M2C_FIELD(arg0, s32 *, 4), arg1);
    func_00308428(M2C_FIELD(arg0, s32 *, 4), arg1);
}
