#include "m2c_macros.h"

extern M2C_UNK func_0019C868 __attribute__((section(".data")));

void func_0019D680(void *arg0) {
    void *temp_v1;

    if ((arg0 != NULL) && (*M2C_FIELD(arg0, s32 **, 0x28) == (s32)0x0019C868u)) {
        temp_v1 = M2C_FIELD(arg0, void **, 0x38);
        M2C_FIELD(temp_v1, u16 *, 0xC24) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xC24) | 4);
    }
}
