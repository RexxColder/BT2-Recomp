#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_00423118 __attribute__((section(".data")));

void func_003CCE98(void) {
    M2C_FIELD(D_00423118, s32 *, 0x144) = M2C_FIELD(D_00423118, s32 *, 0x138) + 2;
    func_2493C0(M2C_FIELD(D_00423118, s32 *, 0x8), 0x342E, 0x3847, 0, M2C_FIELD(D_00423118, s32 *, 0x144));
}
