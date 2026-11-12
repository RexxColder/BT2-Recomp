#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037C038 __attribute__((section(".data")));

s32 func_002EC680(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037C038);
        return -3;
    }
    return M2C_FIELD(arg0, s32 *, 0x18);
}
