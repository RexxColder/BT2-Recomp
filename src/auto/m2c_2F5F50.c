#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037CC88 __attribute__((section(".data")));

s32 func_002F5F50(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037CC88);
        return -1;
    }
    return M2C_FIELD(arg0, s32 *, 0x4C);
}
