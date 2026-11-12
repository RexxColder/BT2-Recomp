#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_00427334 __attribute__((section(".data")));

void func_003E0640(void) {
    M2C_FIELD(D_00427334, s32 *, 0xA0) = M2C_FIELD(D_00427334, s32 *, 0x9C) + 1;
    func_2493C0(M2C_FIELD(D_00427334, s32 *, 0xC), 0x3422, 0x383B, 0, M2C_FIELD(D_00427334, s32 *, 0xA0));
    M2C_FIELD(D_00427334, s32 *, 0xB4) = 0;
    M2C_FIELD(D_00427334, s32 *, 0xB8) = 0;
}
