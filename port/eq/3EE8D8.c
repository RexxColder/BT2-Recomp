#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_00428F4C __attribute__((section(".data")));

void func_003EE8D8(void) {
    if (M2C_FIELD(D_00428F4C, s32 *, 0x174) & 4) {
        M2C_FIELD(D_00428F4C, s32 *, 0x17C) = M2C_FIELD(D_00428F4C, s32 *, 0x178) * 2 + 4;
        M2C_FIELD(D_00428F4C, s32 *, 0x190) = 3;
    } else {
        M2C_FIELD(D_00428F4C, s32 *, 0x17C) = M2C_FIELD(D_00428F4C, s32 *, 0x178) * 2 + 3;
        M2C_FIELD(D_00428F4C, s32 *, 0x190) = 0;
    }
    func_2493C0(M2C_FIELD(D_00428F4C, s32 *, 0xC), 0x3711, 0x3B2A, 0, M2C_FIELD(D_00428F4C, s32 *, 0x17C));
}
