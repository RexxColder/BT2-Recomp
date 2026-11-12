#include "m2c_macros.h"

M2C_UNK func_002BA1C8();                            /* extern */
M2C_UNK func_002BA378(void *);                      /* extern */

void func_002BA180(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x17C) == 0) {
        return;
    }
    func_002BA1C8(arg0);
    func_002BA378(arg0);
}
