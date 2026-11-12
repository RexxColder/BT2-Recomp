#include "m2c_macros.h"

extern M2C_UNK func_001E9428 __attribute__((section(".data")));

void func_001EAD80(void *arg0) {
    u16 temp_v0;
    void *temp_a0;

    if ((arg0 != NULL) && (*M2C_FIELD(arg0, s32 **, 0x28) == (s32)0x001E9428u)) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        temp_v0 = M2C_FIELD(temp_a0, u16 *, 0x124);
        if (temp_v0 & 1 & 0xFFFF) {
            M2C_FIELD(temp_a0, u16 *, 0x124) = (u16) (temp_v0 | 4);
        }
    }
}
