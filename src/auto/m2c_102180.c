#include "m2c_macros.h"

s32 func_00100CB8(M2C_UNK);                         /* extern */
s32 func_0028BAA8(M2C_UNK);                         /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003876A0;

void func_00102180(void) {
    void *var_s0;

    var_s0 = D_003876A0;
    var_s0 += 0x70;
    memset(var_s0, 0, 0x20);
    M2C_FIELD(var_s0, s32 *, 0) = func_00100CB8(0x542);
    M2C_FIELD(var_s0, s32 *, 8) = func_0028BAA8(0x5000);
    M2C_FIELD(var_s0, s32 *, 0xC) = func_0028BAA8(0x12C800);
    M2C_FIELD(var_s0, s32 *, 4) = func_0028BAA8(0x1000);
}
