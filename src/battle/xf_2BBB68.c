#include "m2c_macros.h"

void *func_002BC170();                              /* extern */

void func_002BBB68(s32 arg0, s32 arg1) {
    M2C_UNK (*temp_v0_2)(s32);
    void *temp_v0;

    temp_v0 = func_002BC170(arg0);
    if ((arg1 != 0) && (temp_v0 != NULL)) {
        temp_v0_2 = M2C_FIELD(temp_v0, M2C_UNK (**)(s32), 0x10);
        if (temp_v0_2 != NULL) {
            temp_v0_2(arg1);
        }
    }
}
