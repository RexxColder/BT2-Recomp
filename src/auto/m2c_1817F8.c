#include "m2c_macros.h"

M2C_UNK func_00129C28(s32);                         /* extern */

void func_001817F8(void **arg0) {
    void *temp_a0;

    temp_a0 = *arg0;
    if (temp_a0 != NULL) {
        func_00129C28(M2C_FIELD(temp_a0, s32 *, 0x38) + 0xA0);
    }
}
