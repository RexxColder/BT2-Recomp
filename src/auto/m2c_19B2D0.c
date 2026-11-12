#include "m2c_macros.h"

M2C_UNK func_001CCAC8(s32, void *);                 /* extern */
M2C_UNK func_001CCB20(s32, void *);                 /* extern */

void func_0019B2D0(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    func_001CCAC8(M2C_FIELD(temp_s0, s32 *, 0x28), temp_s0 + 0x30);
    func_001CCB20(M2C_FIELD(temp_s0, s32 *, 0x28), temp_s0 + 0x40);
}
