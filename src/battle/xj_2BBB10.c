#include "m2c_macros.h"

void *func_002BC170();                              /* extern */

s32 func_002BBB10(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 (*temp_v0_2)(M2C_UNK, M2C_UNK);
    s32 var_v1;
    void *temp_v0;

    temp_v0 = func_002BC170(arg0);
    var_v1 = 0;
    if (temp_v0 != NULL) {
        temp_v0_2 = M2C_FIELD(temp_v0, s32 (**)(M2C_UNK, M2C_UNK), 0xC);
        if (temp_v0_2 != NULL) {
            var_v1 = temp_v0_2(arg1, arg2);
        }
    }
    return var_v1;
}
