#include "m2c_macros.h"

void *func_002A3DB8(M2C_UNK);                       /* extern */

s32 func_002A6E40(s32 arg0) {
    if (arg0 == 0) {
        M2C_FIELD(func_002A3DB8(0x20), s8 *, 0x18) = 0;
    }
    return 1;
}
