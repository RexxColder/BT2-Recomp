#include "m2c_macros.h"

extern void *D_00421C98 __attribute__((section(".data")));

void func_003C08D8(s32 arg0) {
    if (arg0 == 0) {
        M2C_FIELD(D_00421C98, s32 *, 0xCC) = (s32) M2C_FIELD(M2C_FIELD(D_00421C98, void **, 0x98), s32 *, 0x10);
        M2C_FIELD(D_00421C98, s32 *, 0xD0) = (s32) M2C_FIELD(M2C_FIELD(D_00421C98, void **, 0x98), s32 *, 0x10);
        M2C_FIELD(D_00421C98, s32 *, 0xD4) = (s32) M2C_FIELD(M2C_FIELD(D_00421C98, void **, 0x98), s32 *, 0x10);
        return;
    }
    M2C_FIELD(D_00421C98, s32 *, 0xD8) = (s32) M2C_FIELD(M2C_FIELD(D_00421C98, void **, 0x9C), s32 *, 0x10);
    M2C_FIELD(D_00421C98, s32 *, 0xDC) = (s32) M2C_FIELD(M2C_FIELD(D_00421C98, void **, 0x9C), s32 *, 0x10);
    M2C_FIELD(D_00421C98, s32 *, 0xE0) = (s32) M2C_FIELD(M2C_FIELD(D_00421C98, void **, 0x9C), s32 *, 0x10);
}
