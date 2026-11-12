#include "m2c_macros.h"

M2C_UNK func_002C35E0(void *);                      /* extern */
s32 func_002C3640(void *);                          /* extern */
s32 func_002C47A8();                                /* extern */
M2C_UNK func_002C4A50(void *);                      /* extern */

s32 func_002C3568(void *arg0) {
    s32 temp_s1;

    if (func_002C47A8(arg0) == 1) {
        return 0;
    }
    func_002C35E0(arg0);
    temp_s1 = func_002C3640(arg0);
    if (M2C_FIELD(arg0, s32 *, 0x48) == 2) {
        func_002C4A50(arg0);
    }
    return temp_s1;
}
