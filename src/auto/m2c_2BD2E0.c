#include "m2c_macros.h"

M2C_UNK func_002B7BF0();                            /* extern */
M2C_UNK func_002B7C08();                            /* extern */
M2C_UNK func_002BC600();                            /* extern */
M2C_UNK func_002BC670(s32);                         /* extern */
M2C_UNK func_002BD250(s32, M2C_UNK);                /* extern */

void func_002BD2E0(s32 arg0) {
    func_002B7BF0(arg0);
    func_002BD250(arg0, 1);
    func_002BC600();
    func_002BD250(arg0, 0);
    func_002B7C08();
    func_002BC670(arg0);
}
