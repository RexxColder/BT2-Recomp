#include "m2c_macros.h"

M2C_UNK func_001EDBA8(s32, M2C_UNK);                /* extern */

void func_001AC618(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 *, 0x11C);
    if (temp_v1 != -1) {
        func_001EDBA8(temp_v1, -1);
    }
}
