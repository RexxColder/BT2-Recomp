#include "m2c_macros.h"

M2C_UNK func_00180638(s32, s32);                    /* extern */
void *memset(void *, s32, s32);                     /* extern */

void func_001803E0(void **arg0) {
    s32 var_a1;
    void **temp_s0;
    void **var_a0;
    void *temp_v0;
    void *temp_v1;

    var_a0 = arg0;
    var_a1 = 0x1D;
    temp_s0 = var_a0;
    do {
        temp_v0 = *var_a0;
        var_a0 += 1;
        if (temp_v0 != NULL) {
            temp_v1 = M2C_FIELD(temp_v0, void **, 0x38);
            M2C_FIELD(temp_v1, s32 *, 0x48) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x48) | 4);
        }
        var_a1 -= 1;
    } while (var_a1 >= 0);
    func_00180638(M2C_FIELD(temp_s0, s32 *, 0x78), var_a1);
    memset(temp_s0, 0, 0x80);
}
