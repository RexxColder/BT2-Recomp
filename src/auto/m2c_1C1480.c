#include "m2c_macros.h"

void func_001C1480(void *arg0, s32 arg1) {
    void *temp_a0;

    if (arg0 != NULL) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if (temp_a0 != NULL) {
            M2C_FIELD(temp_a0, s32 *, 0xAC0) = arg1;
        }
    }
}
