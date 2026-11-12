#include "m2c_macros.h"

extern void *D_00387A40;
extern s32 D_003B2654 __attribute__((section(".data")));

void func_002619C8(s32 arg0) {
    void *temp_v1;

    if (!(D_003B2654 & 0x100)) {
        temp_v1 = M2C_FIELD(D_00387A40, s32 *, 8) + ((arg0 & 0xFFFF) * 0x1520);
        M2C_FIELD(temp_v1, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xAF0) | 0x80);
    }
}
