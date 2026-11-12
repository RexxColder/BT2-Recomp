#include "m2c_macros.h"

extern M2C_UNK func_001AC650 __attribute__((section(".data")));

void func_001AC968(void *arg0, void *arg1) {
    void *temp_a0;

    if ((arg0 != NULL) && !(M2C_FIELD(arg0, u8 *, 0) & 1 & 0xFF) && (*M2C_FIELD(arg0, s32 **, 0x28) == (s32)0x001AC650u)) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        M2C_FIELD(temp_a0, s64 *, 0x80) = (s64) M2C_FIELD(arg1, s64 *, 0);
        M2C_FIELD(temp_a0, s64 *, 0x88) = (s64) M2C_FIELD(arg1, s64 *, 8);
        M2C_FIELD(temp_a0, s64 *, 0x90) = (s64) M2C_FIELD(arg1, s64 *, 0x10);
        M2C_FIELD(temp_a0, s64 *, 0x98) = (s64) M2C_FIELD(arg1, s64 *, 0x18);
        M2C_FIELD(temp_a0, s64 *, 0xA0) = (s64) M2C_FIELD(arg1, s64 *, 0x20);
        M2C_FIELD(temp_a0, s64 *, 0xA8) = (s64) M2C_FIELD(arg1, s64 *, 0x28);
        M2C_FIELD(temp_a0, s64 *, 0xB0) = (s64) M2C_FIELD(arg1, s64 *, 0x30);
        M2C_FIELD(temp_a0, s64 *, 0xB8) = (s64) M2C_FIELD(arg1, s64 *, 0x38);
    }
}
