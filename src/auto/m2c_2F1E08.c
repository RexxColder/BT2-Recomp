#include "m2c_macros.h"

M2C_UNK func_002F2108();                            /* extern */
M2C_UNK func_002F3378();                            /* extern */
M2C_UNK func_002F3390();                            /* extern */

void func_002F1E08(void *arg0) {
    s8 temp_v1;

    func_002F2108(arg0);
    func_002F3378();
    temp_v1 = M2C_FIELD(arg0, s8 *, 0x49);
    if (temp_v1 == 1) {
        M2C_FIELD(arg0, s8 *, 0x46) = temp_v1;
    }
    M2C_FIELD(arg0, s8 *, 0x45) = 0;
    func_002F3390();
}
