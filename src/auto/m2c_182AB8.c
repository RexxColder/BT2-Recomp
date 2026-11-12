#include "m2c_macros.h"

extern M2C_UNK func_00182728 __attribute__((section(".data")));

void func_00182AB8(void *arg0) {
    void *temp_a0;

    if ((arg0 != NULL) && (*M2C_FIELD(arg0, s32 **, 0x28) == (s32)0x00182728u) && !(M2C_FIELD(arg0, u8 *, 0) & 1 & 0xFF)) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if (temp_a0 != NULL) {
            M2C_FIELD(temp_a0, s32 *, 0xA80) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xA80) | 0xE);
        }
    }
}
