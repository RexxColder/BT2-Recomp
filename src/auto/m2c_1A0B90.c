#include "m2c_macros.h"

extern void *D_00387808;
extern M2C_UNK func_0019FFA8 __attribute__((section(".data")));

void func_001A0B90(void) {
    void *temp_a1;
    void *temp_v1;

    if (D_00387808 != NULL) {
        temp_a1 = M2C_FIELD(D_00387808, void **, 0x5B0);
        if ((temp_a1 != NULL) && (*M2C_FIELD(temp_a1, s32 **, 0x28) == (s32)0x0019FFA8u) && !(M2C_FIELD(temp_a1, u8 *, 0) & 1 & 0xFF)) {
            temp_v1 = M2C_FIELD(temp_a1, void **, 0x38);
            M2C_FIELD(temp_v1, s32 *, 0x28) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x28) | 0x20);
        }
    }
}
