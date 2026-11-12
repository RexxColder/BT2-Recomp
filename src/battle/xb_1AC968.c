#include "m2c_macros.h"

void func_001AC650(void);

// Copies 0x40 bytes of the 64-bit-word block arg1 into obj->0x38 +0x80..0xB8 when arg0 is live and its +0x28 vtable entry is func_001AC650.
void func_001AC968(void *arg0, void *arg1) {
    void *temp_a0;
    s32 *temp_v1;

    if ((arg0 != NULL) && !(M2C_FIELD(arg0, u8 *, 0) & 1 & 0xFF)) {
        temp_v1 = M2C_FIELD(arg0, s32 **, 0x28);
        if (*temp_v1 == (s32) func_001AC650) {
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
}
