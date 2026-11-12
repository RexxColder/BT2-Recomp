#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_00421380 __attribute__((section(".data")));

void func_003B3DE8(void) {
    M2C_FIELD(D_00421380, s32 *, 0x100) = 0;
    M2C_FIELD(D_00421380, s32 *, 0x104) = 0;
    M2C_FIELD(D_00421380, s32 *, 0xEC) = M2C_FIELD(D_00421380, s32 *, 0xE8) + 9;
    M2C_FIELD(D_00421380, s32 *, 0xF4) = (M2C_FIELD(D_00421380, s32 *, 0xE8) ^ 1) & 1;
    func_2493C0(M2C_FIELD(D_00421380, s32 *, 0xC), 0x36DC, 0x3AF5, 0, M2C_FIELD(D_00421380, s32 *, 0xEC));
}
