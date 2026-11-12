#include "m2c_macros.h"

M2C_UNK func_002FD710(void *);                      /* extern */
M2C_UNK func_002FDB78();                            /* extern */

void func_002FD8A8(void *arg0) {
    if (arg0 != NULL) {
        if ((u8) M2C_FIELD(arg0, u8 *, 2) >= 2U) {
            func_002FDB78(arg0);
        }
        M2C_FIELD(arg0, s8 *, 0) = 0;
        func_002FD710(arg0);
    }
}
