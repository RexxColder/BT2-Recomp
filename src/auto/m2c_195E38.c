#include "m2c_macros.h"

M2C_UNK func_0014EEF8(s32, void *);                 /* extern */

void func_00195E38(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x38);
    func_0014EEF8(M2C_FIELD(temp_a1, s32 *, 0xA00), temp_a1);
}
