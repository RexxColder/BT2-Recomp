#include "m2c_macros.h"

void *func_002B1DD0(M2C_UNK);                       /* extern */
extern s32 D_00387E18;

s32 func_0020C950(void) {
    if (D_00387E18 != 0) {
        return M2C_FIELD(func_002B1DD0(0), s32 *, 0x18);
    }
    return 0;
}
