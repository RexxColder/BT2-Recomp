#include "m2c_macros.h"

M2C_UNK func_003007F8(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037E9D8 __attribute__((section(".data")));

s32 func_003001F0(void *arg0) {
    if (arg0 == NULL) {
        func_003007F8(&D_0037E9D8);
        return -1;
    }
    return M2C_FIELD(arg0, s32 *, 0x24);
}
