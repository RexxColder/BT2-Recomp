#include "m2c_macros.h"

void *func_002CABA0(void *arg0, s32 arg1) {
    void *temp_v0;
    s32 temp_a2;
    void *var_a0;
    void *var_v0;
    void *var_v1;
    s32 var_a3;

    temp_v0 = M2C_FIELD(arg0, void **, 0x1FC0);
    var_a3 = 0;
    temp_a2 = M2C_FIELD(temp_v0, s32 *, 0x178);
    var_v1 = temp_v0 + 0x180;
    var_v0 = NULL;
    if (temp_a2 > 0) {
        var_a0 = arg0 + 0x16B0;
        do {
            if (var_v1 == (void *) arg1) {
                return var_a0;
            }
            var_a3 += 1;
            var_v1 += 0xF0;
            var_a0 += 0x88;
        } while (var_a3 < temp_a2);
    }
    return var_v0;
}
