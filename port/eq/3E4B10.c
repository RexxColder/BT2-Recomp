#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_004279CC __attribute__((section(".data")));

void func_003E4B10(void) {
    s32 var_v0;

    M2C_FIELD(D_004279CC, s32 *, 0xE0) = 0;
    M2C_FIELD(D_004279CC, s32 *, 0xE4) = 0;
    if (!(M2C_FIELD(D_004279CC, s32 *, 0xD0) & 4)) {
        var_v0 = M2C_FIELD(D_004279CC, s32 *, 0xD4) + 1;
    } else {
        var_v0 = M2C_FIELD(D_004279CC, s32 *, 0xDC) + 6;
    }
    M2C_FIELD(D_004279CC, s32 *, 0xD8) = var_v0;
    func_2493C0(M2C_FIELD(D_004279CC, s32 *, 0x8), 0x36EF, 0x3B08, 0, M2C_FIELD(D_004279CC, s32 *, 0xD8));
}
