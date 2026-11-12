#include "m2c_macros.h"

M2C_UNK func_001B56D8(s32, M2C_UNK);                /* extern */

void func_00204C68(void *arg0) {
    s64 temp_s1;

    temp_s1 = M2C_FIELD(arg0, s64 *, 0x338);
    if (temp_s1 & 0x2000) {
        func_001B56D8(M2C_FIELD(arg0, s32 *, 0x1534), 0);
    }
    if (temp_s1 & 0x4000) {
        func_001B56D8(M2C_FIELD(arg0, s32 *, 0x1534), 1);
    }
}
