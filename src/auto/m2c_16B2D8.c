#include "m2c_macros.h"

void *func_0016B2D8(s32 arg0) {
    void *temp_v0;

    temp_v0 = arg0 + 0xD10;
    return (M2C_FIELD(temp_v0, s32 *, 0x20) != 0) ? NULL : temp_v0;
}
