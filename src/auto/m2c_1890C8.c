#include "m2c_macros.h"

M2C_UNK func_001889F8();                            /* extern */
M2C_UNK func_00188D68();                            /* extern */

void func_001890C8(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s32 *, 0xA4) & 2) {
        func_001889F8(arg0);
        return;
    }
    func_00188D68(arg0);
}
