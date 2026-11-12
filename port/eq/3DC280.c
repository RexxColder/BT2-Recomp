#include "m2c_macros.h"

s32 func_1018B8(void *);
void func_2493C0(s32, s32, s32, s32, s32);
void func_26E9E8(void *);
extern void *D_004263EC __attribute__((section(".data")));

void func_003DC280(void) {
    if (M2C_FIELD(D_004263EC, s32 *, 0x78) == 0 && M2C_FIELD(D_004263EC, s32 *, 0x74) != 0 &&
        M2C_FIELD(D_004263EC, s32 *, 0x68) == 0) {
        if (func_1018B8(D_004263EC) == 5) {
            M2C_FIELD(D_004263EC, s32 *, 0x68) = M2C_FIELD(D_004263EC, s32 *, 0x64) + 1;
            func_2493C0(M2C_FIELD(D_004263EC, s32 *, 0xC), 0x36B2, 0x3ACB, 0, M2C_FIELD(D_004263EC, s32 *, 0x68));
        }
    }
    func_26E9E8((u8 *)D_004263EC + 0x10);
}
