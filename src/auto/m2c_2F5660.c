#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern s32 D_00354ED4 __attribute__((section(".data")));
extern M2C_UNK D_0037CA70 __attribute__((section(".data")));

void func_002F5660(void *arg0, s32 arg1) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037CA70);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x38) = arg1;
    D_00354ED4 = arg1;
}
