#include "m2c_macros.h"

M2C_UNK func_00308CF0();                            /* extern */
M2C_UNK func_00308EA8();                            /* extern */

void func_00309028(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x9C) == 1) {
        func_00308EA8(arg0);
        return;
    }
    func_00308CF0(arg0);
}
