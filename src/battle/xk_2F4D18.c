#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
s32 func_002F1540(s32);                             /* extern */
extern M2C_UNK D_0037C830 __attribute__((section(".data")));

s32 adxt_GetSfreq(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037C830);
        return -1;
    }
    return (M2C_FIELD(arg0, s8 *, 1) < 2) ? 0 : func_002F1540(M2C_FIELD(arg0, s32 *, 4));
}
