#include "m2c_macros.h"

void *func_001272E0();                              /* extern */
s32 func_0023F908(void *);                          /* extern */

s32 func_00218758(void *arg0) {
    s16 temp_v1_2;
    s32 temp_v1;
    s32 var_a2;
    s32 var_s1;
    void *temp_a0;
    void *temp_v0;
    void *var_a1;

    var_s1 = 0;
    temp_v0 = func_001272E0();
    temp_v1 = M2C_FIELD(temp_v0, s32 *, 0x6000);
    if (temp_v1 > 0) {
        var_a1 = temp_v0;
        var_a2 = temp_v1;
        do {
            if (M2C_FIELD(var_a1, s32 *, 0xC) == 0) {
                temp_a0 = M2C_FIELD(var_a1, void **, 0x68);
                if ((temp_a0 != NULL) && (M2C_FIELD(temp_a0, s16 *, 0x10) == M2C_FIELD(arg0, s32 *, 0x1534)) && (M2C_FIELD(var_a1, s32 *, 0x54) != 1) && (M2C_FIELD(var_a1, s8 *, 0x5C) == 0)) {
                    temp_v1_2 = M2C_FIELD(temp_a0, s16 *, 0x18);
                    if (temp_v1_2 != 4) {
                        if (temp_v1_2 < 5) {
                            if (temp_v1_2 != 0) {
                                goto block_13;
                            }
                        } else if (temp_v1_2 != 8) {
block_13:
                            var_s1 += 1;
                        }
                    }
                }
            }
            var_a2 -= 1;
            var_a1 += 0x180;
        } while (var_a2 != 0);
    }
    return var_s1 < func_0023F908(arg0);
}
