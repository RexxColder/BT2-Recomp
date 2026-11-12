#include "m2c_macros.h"

extern M2C_UNK func_0019C868 __attribute__((section(".data")));

void func_0019D6B8(void *arg0, s32 arg1) {
    if ((arg0 != NULL) && (*M2C_FIELD(arg0, s32 **, 0x28) == (s32)0x0019C868u)) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 *, 0xC20) = arg1;
    }
}
