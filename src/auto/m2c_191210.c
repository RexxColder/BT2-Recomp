#include "m2c_macros.h"

M2C_UNK func_0014EEF8(s32, void *);                 /* extern */

void func_00191210(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x38);
    M2C_FIELD(temp_v0, s32 *, 0x30) = 0;
    func_0014EEF8(M2C_FIELD(temp_v0, s32 *, 4), temp_v0 + 0x60);
}
