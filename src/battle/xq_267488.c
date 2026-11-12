#include "m2c_macros.h"

s32 func_00267488(void *arg0) {
    void *temp_a = (char *) arg0 + 0xDF0;
    if (M2C_FIELD(arg0, s32 *, 0x54) != 0) {
        return M2C_FIELD(temp_a, s32 *, 8) - 1;
    }
    return -1;
}
