#include "m2c_macros.h"

extern s32 D_0038787C;
extern M2C_UNK func_001B5400 __attribute__((section(".data")));

void func_001B5630(void *arg0) {
    void *temp_v1;

    if ((D_0038787C != 0) && (arg0 != NULL) && (*M2C_FIELD(arg0, s32 **, 0x28) == (s32)0x001B5400u) && !(M2C_FIELD(arg0, u8 *, 0) & 1 & 0xFF)) {
        temp_v1 = M2C_FIELD(arg0, void **, 0x38);
        M2C_FIELD(temp_v1, s32 *, 0x54) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x54) | 1);
    }
}
