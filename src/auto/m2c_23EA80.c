#include "m2c_macros.h"

s32 func_0023EA80(void *arg0, u32 arg1) {
    if (arg1 >= 0x6AU) {
        return M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x974);
    }
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x974) + (arg1 * 0x64);
}
