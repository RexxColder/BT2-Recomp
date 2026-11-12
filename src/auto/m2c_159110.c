#include "m2c_macros.h"

M2C_UNK func_00147FD0(s32);                         /* extern */
M2C_UNK func_00158FF8(void *);                      /* extern */

void func_00159110(void *arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), void **, 8);
    if (M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), s32 *, 4) != 0) {
        func_00147FD0(M2C_FIELD(temp_a0, s32 *, 0));
    }
    func_00158FF8(arg0);
}
