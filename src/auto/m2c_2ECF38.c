#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037C1D0 __attribute__((section(".data")));

void func_002ECF38(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s8 *, 1) == 2) {
        func_002EA050(&D_0037C1D0);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x30) = arg1;
}
