#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_004263EC __attribute__((section(".data")));

void func_003DC050(void) {
    M2C_FIELD(D_004263EC, s32 *, 0x68) = M2C_FIELD(D_004263EC, s32 *, 0x64) + 1;
    func_2493C0(M2C_FIELD(D_004263EC, s32 *, 0xC), 0x36B2, 0x3ACB, 0, M2C_FIELD(D_004263EC, s32 *, 0x68));
}
