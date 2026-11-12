#include "m2c_macros.h"

M2C_UNK func_001EC4C0();                            /* extern */
M2C_UNK func_001ECB18();                            /* extern */

void func_001EC460(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x68) & 8) {
        func_001EC4C0(arg0);
        return;
    }
    func_001ECB18(arg0);
}
