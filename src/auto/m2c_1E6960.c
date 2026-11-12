#include "m2c_macros.h"

M2C_UNK func_001E5568(s32);                         /* extern */

void func_001E6960(void *arg0) {
    void *temp_a0;

    if (arg0 != NULL) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if ((M2C_FIELD(temp_a0, s64 *, 0) & 5) == 1) {
            func_001E5568(M2C_FIELD(temp_a0, s32 *, 0x40));
        }
    }
}
