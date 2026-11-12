#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
s32 func_002F2CE0(s32);                             /* extern */
extern M2C_UNK D_0037C0C0 __attribute__((section(".data")));

s32 func_002EC858(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037C0C0);
        return -3;
    }
    return func_002F2CE0(M2C_FIELD(arg0, s32 *, 4));
}
