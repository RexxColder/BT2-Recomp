#include "m2c_macros.h"

void *func_001272E0();                              /* extern */
s16 func_00127C30(void *);                          /* extern */

void func_00127BB8(void) {
    s32 var_s2;
    void *temp_v0;
    void *var_s0;

    var_s2 = 0;
    temp_v0 = func_001272E0();
    if (M2C_FIELD(temp_v0, s32 *, 0x6000) > 0) {
        var_s0 = temp_v0;
        do {
            if (M2C_FIELD(var_s0, void **, 0x60) != NULL) {
                M2C_FIELD(M2C_FIELD(var_s0, void **, 0x60), s16 *, 8) = func_00127C30(var_s0);
            }
            var_s2 += 1;
            var_s0 += 0x180;
        } while (var_s2 < M2C_FIELD(temp_v0, s32 *, 0x6000));
    }
}
