#include "m2c_macros.h"

void func_001E67E0(void *arg0) {
    s32 *temp_a0;
    s32 temp_v0;

    if (arg0 != NULL) {
        temp_a0 = M2C_FIELD(arg0, s32 **, 0x38);
        temp_v0 = *temp_a0;
        if (temp_v0 & 1) {
            *temp_a0 = temp_v0 | 8;
        }
    }
}
