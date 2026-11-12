#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037C0F8 __attribute__((section(".data")));

s32 func_002EC8D8(void *arg0, s32 *arg1) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037C0F8);
        *arg1 = 0;
        return -3;
    }
    *arg1 = M2C_FIELD(arg0, s32 *, 0x1C);
    return M2C_FIELD(arg0, s32 *, 0x20);
}
