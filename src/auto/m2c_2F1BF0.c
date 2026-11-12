#include "m2c_macros.h"

M2C_UNK func_002F1E48(s8 *);                        /* extern */
M2C_UNK func_002F21A0();                            /* extern */
M2C_UNK memset(s8 *, M2C_UNK, M2C_UNK);             /* extern */

void func_002F1BF0(s8 *arg0) {
    if (arg0 != NULL) {
        func_002F21A0(arg0);
        func_002F1E48(arg0);
        *arg0 = 0;
        memset(arg0, 0, 0x60);
    }
}
