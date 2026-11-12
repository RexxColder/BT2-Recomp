#include "m2c_macros.h"

extern s32 *D_00387AEC;

void func_0027B9B8(void) {
    s32 *temp_v1;
    s32 var_a1;
    s32 var_a2;

    if (D_00387AEC != NULL) {
        var_a2 = 0;
        var_a1 = 9;
        do {
            temp_v1 = M2C_FIELD(D_00387AEC, s32 *, 0) + var_a2;
            var_a2 += 0x460;
            if (*temp_v1 != 0) {
                *temp_v1 = 0;
            }
            var_a1 -= 1;
        } while (var_a1 >= 0);
        M2C_FIELD(D_00387AEC, s32 *, 0xA8) = 0;
        M2C_FIELD(D_00387AEC, s32 *, 0xAC) = 0;
    }
}
