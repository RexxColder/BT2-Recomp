#include "m2c_macros.h"

M2C_UNK func_00184880();                            /* extern */
M2C_UNK func_00184BE0();                            /* extern */

void func_00184F18(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s32 *, 0xA4) & 2) {
        func_00184880(arg0);
        return;
    }
    func_00184BE0(arg0);
}
