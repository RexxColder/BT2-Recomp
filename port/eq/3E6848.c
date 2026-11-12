#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_004279D0 __attribute__((section(".data")));

void func_003E6848(void) {
    s32 temp_v0;

    M2C_FIELD(D_004279D0, s32 *, 0x2FC) = 0;
    M2C_FIELD(D_004279D0, s32 *, 0x300) = 0;
    if (!(M2C_FIELD(D_004279D0, s32 *, 0xF0) & 2)) {
        temp_v0 = M2C_FIELD(D_004279D0, s32 *, 0xF4);
        if (temp_v0 == 3) {
            M2C_FIELD(D_004279D0, s32 *, 0xEC) = 0xC;
        } else {
            M2C_FIELD(D_004279D0, s32 *, 0xEC) = temp_v0 + 0x16;
        }
    } else {
        M2C_FIELD(D_004279D0, s32 *, 0xEC) = M2C_FIELD(D_004279D0, s32 *, 0xF8) + 0x19;
    }
    func_2493C0(M2C_FIELD(D_004279D0, s32 *, 0xC), 0x36EF, 0x3B08, 0, M2C_FIELD(D_004279D0, s32 *, 0xEC));
}
