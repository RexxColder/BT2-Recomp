#include "m2c_macros.h"

M2C_UNK func_002FFF90();                            /* extern */
M2C_UNK memset(s8 *, M2C_UNK, M2C_UNK);             /* extern */

void func_002FFB70(s8 *arg0) {
    if (arg0 != NULL) {
        func_002FFF90(arg0);
        *arg0 = 0;
        memset(arg0, 0, 0x238);
    }
}
