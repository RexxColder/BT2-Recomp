#include "m2c_macros.h"

extern void *D_0042A590 __attribute__((section(".data")));

void func_003FFD00(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_0042A590, s32 *, 0x208);
    if (temp_v0 & 0x80) {
        M2C_FIELD(D_0042A590, s32 *, 0x208) = (s32) (temp_v0 ^ 0x80);
        M2C_FIELD(D_0042A590, s32 *, 0x208) = (s32) (M2C_FIELD(D_0042A590, s32 *, 0x208) & ~0x10);
        M2C_FIELD(D_0042A590, s32 *, 0x208) = (s32) (M2C_FIELD(D_0042A590, s32 *, 0x208) & ~0x20);
    }
    M2C_FIELD(D_0042A590, s32 *, 0x208) = (s32) (M2C_FIELD(D_0042A590, s32 *, 0x208) | 0x40);
}
