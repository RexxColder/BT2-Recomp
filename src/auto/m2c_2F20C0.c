#include "m2c_macros.h"

M2C_UNK func_002F1FC8(void *);                      /* extern */
M2C_UNK func_002F3378();                            /* extern */
M2C_UNK func_002F3390();                            /* extern */

s32 func_002F20C0(void *arg0, s32 arg1) {
    func_002F3378(arg0, arg1);
    func_002F1FC8(arg0);
    M2C_FIELD(arg0, s32 *, 0x5C) = arg1;
    func_002F3390();
    return 1;
}
