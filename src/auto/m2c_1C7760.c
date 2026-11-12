#include "m2c_macros.h"

M2C_UNK func_001C85D0(s32);                         /* extern */

void func_001C7760(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 4);
    if (temp_v1 != 0) {
        func_001C85D0(temp_v1);
    }
}
