#include "m2c_macros.h"

M2C_UNK func_00308448(s32);                         /* extern */
M2C_UNK func_003086A0(s32);                         /* extern */

void func_002F0420(void *arg0) {
    func_003086A0(M2C_FIELD(arg0, s32 *, 4));
    func_00308448(M2C_FIELD(arg0, s32 *, 4));
}
