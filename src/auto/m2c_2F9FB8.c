#include "m2c_macros.h"

extern void *D_0039D938 __attribute__((section(".data")));

void func_002F9FB8(void) {
    M2C_UNK (*temp_v0_2)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
    s32 var_s1;
    void **var_s0;
    void *temp_v0;

    var_s0 = &D_0039D938;
    var_s1 = 0x1F;
    do {
        temp_v0 = *var_s0;
        var_s0 += 4;
        if (temp_v0 != NULL) {
            temp_v0_2 = M2C_FIELD(temp_v0, M2C_UNK (**)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK), 0x60);
            if (temp_v0_2 != NULL) {
                temp_v0_2(0, 0x190, 0, 0);
            }
        }
        var_s1 -= 1;
    } while (var_s1 >= 0);
}
