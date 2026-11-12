#include "m2c_macros.h"

extern M2C_UNK func_00183228 __attribute__((section(".data")));

void func_00182BB0(void *arg0) {
    void *temp_v1;

    if ((arg0 != NULL) && (*M2C_FIELD(arg0, s32 **, 0x28) == (s32)0x00183228u) && !(M2C_FIELD(arg0, u8 *, 0) & 1 & 0xFF)) {
        temp_v1 = M2C_FIELD(arg0, void **, 0x38);
        M2C_FIELD(temp_v1, u16 *, 0xAD6) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xAD6) | 0x2400);
    }
}
