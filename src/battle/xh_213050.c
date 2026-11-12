#include "m2c_macros.h"

M2C_UNK func_00101700(s32);                         /* extern */
s32 func_00101720(s32);                             /* extern */
s32 func_00211310(s32, M2C_UNK, M2C_UNK);                /* extern */

// If func_00211310(arg0,9,0x04000000) is set and func_00101720(field 0x1534) == 3, calls func_00101700 on field 0x1534.
void func_00213050(void *arg0) {
    if (func_00211310(arg0, 9, 0x04000000) == 0) {
        return;
    }
    if (func_00101720(M2C_FIELD(arg0, s32 *, 0x1534)) != 3) {
        return;
    }
    func_00101700(M2C_FIELD(arg0, s32 *, 0x1534));
}
