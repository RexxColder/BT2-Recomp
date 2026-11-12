#include "m2c_macros.h"

M2C_UNK func_0014EEF8(s32, void *);                 /* extern */
M2C_UNK func_00183AB8(void *);                      /* extern */

void func_001831E0(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    func_00183AB8(temp_s0);
    func_0014EEF8(M2C_FIELD(temp_s0, s32 *, 0xA00), temp_s0);
}
