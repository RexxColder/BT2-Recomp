#include "m2c_macros.h"

s32 func_002BC1A0();                                /* extern */

void func_002BBC08(void *arg0) {
    M2C_UNK (*temp_v0)(s32);
    s32 temp_v1;
    void *temp_a0;

    if (func_002BC1A0(arg0) == 1) {
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x1C);
        temp_a0 = M2C_FIELD(arg0, void **, 8);
        if ((temp_v1 != 0) && (temp_a0 != NULL)) {
            temp_v0 = M2C_FIELD(temp_a0, M2C_UNK (**)(s32), 0x18);
            if (temp_v0 != NULL) {
                temp_v0(temp_v1);
            }
        }
    }
}
