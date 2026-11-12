#include "m2c_macros.h"

M2C_UNK func_001B0D88(void *);                      /* extern */
extern void *D_00387870;

void func_001B2F70(void *arg0) {
    s32 var_s1;
    void *temp_v0;
    void *var_s0;

    var_s1 = 0xF;
    temp_v0 = M2C_FIELD(arg0, void **, 0x38);
    M2C_FIELD(temp_v0, s32 *, 0xA40) = 0;
    var_s0 = temp_v0 + 0x40;
    do {
        var_s1 -= 1;
        func_001B0D88(var_s0);
        M2C_FIELD(var_s0, s32 *, 8) = 0;
        var_s0 += 0xA0;
    } while (var_s1 >= 0);
    M2C_FIELD(D_00387870, s32 *, 8) = (s32) (M2C_FIELD(D_00387870, s32 *, 8) - 1);
}
