#include "m2c_macros.h"

void func_002CF9B8(void *arg0, s32 arg1, s32 arg2) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x36B0);
    if (temp_v1 != NULL) {
        if (M2C_FIELD(temp_v1, s32 *, 0xDB8) < 0) {
            M2C_FIELD(temp_v1, s32 *, 0xDB8) = arg1;
        }
        if (M2C_FIELD(temp_v1, s32 *, 0xDBC) < 0) {
            M2C_FIELD(temp_v1, s32 *, 0xDBC) = arg2;
        }
    }
}
