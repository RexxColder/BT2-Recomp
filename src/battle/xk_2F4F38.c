#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
s32 func_002F1750(s32);                             /* extern */
extern M2C_UNK D_0037C8F0 __attribute__((section(".data")));

s32 func_002F4F38(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037C8F0);
        return -1;
    }
    return (M2C_FIELD(arg0, s8 *, 1) < 2) ? 0 : func_002F1750(M2C_FIELD(arg0, s32 *, 4));
}
