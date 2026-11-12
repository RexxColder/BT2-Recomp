#include "m2c_macros.h"

void func_002CC9A0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x1FC0) + 0x1128;
    M2C_FIELD(temp_v1, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xC) - 1);
}
