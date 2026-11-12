#include "m2c_macros.h"

void func_001C1238(void *arg0) {
    void *temp_a0;

    if (arg0 != NULL) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if (temp_a0 != NULL) {
            M2C_FIELD(temp_a0, s32 *, 0xACC) = 2;
        }
    }
}
