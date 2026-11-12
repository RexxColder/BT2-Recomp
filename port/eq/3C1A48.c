#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_00421C98 __attribute__((section(".data")));

void func_003C1A48(void) {
    M2C_FIELD(D_00421C98, s32 *, 0x154) = 0;
    M2C_FIELD(D_00421C98, s32 *, 0x158) = 0;
    M2C_FIELD(D_00421C98, s32 *, 0x12C) = M2C_FIELD(D_00421C98, s32 *, 0x128) + 1;
    func_2493C0(M2C_FIELD(D_00421C98, s32 *, 0x8), 0x33E9, 0x3802, 0, M2C_FIELD(D_00421C98, s32 *, 0x12C));
}
