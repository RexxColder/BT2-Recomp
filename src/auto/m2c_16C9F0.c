#include "m2c_macros.h"

M2C_UNK func_0014E970(void *);                      /* extern */

void func_0016C9F0(void *arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x38);
    if (M2C_FIELD(temp_a0, u8 *, 0x1E80) != 0) {
        func_0014E970(temp_a0);
    }
}
