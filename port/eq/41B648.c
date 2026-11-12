#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_0042BB84 __attribute__((section(".data")));

void func_0041B648(void) {
    s32 var_v0;

    if (!(M2C_FIELD(D_0042BB84, s32 *, 0xF0) & 4)) {
        var_v0 = M2C_FIELD(D_0042BB84, s32 *, 0xF4) + 1;
    } else {
        var_v0 = M2C_FIELD(D_0042BB84, s32 *, 0xFC) + 5;
    }
    M2C_FIELD(D_0042BB84, s32 *, 0xF8) = var_v0;
    func_2493C0(M2C_FIELD(D_0042BB84, s32 *, 0x8), 0x36A3, 0x3ABC, 0, M2C_FIELD(D_0042BB84, s32 *, 0xF8));
}
