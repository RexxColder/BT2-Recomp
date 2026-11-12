#include "m2c_macros.h"

M2C_UNK func_001A22D0(void *);                      /* extern */

void func_001A4590(void *arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x38);
    M2C_FIELD(temp_a0, s32 *, 0x50) = 0;
    func_001A22D0(temp_a0);
}
