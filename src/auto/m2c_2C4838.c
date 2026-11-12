#include "m2c_macros.h"

void func_002C4838(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x1F7C);
    M2C_FIELD(temp_v1, s32 *, 0x20) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x20) + 1);
}
