#include "m2c_macros.h"

void *func_002BC158();                              /* extern */
M2C_UNK (**func_002BC170(s32))();                   /* extern */

void func_002BB9C8(s32 arg0) {
    M2C_UNK (**temp_v0)();
    M2C_UNK (*temp_v1)();
    void *temp_s1;

    temp_s1 = func_002BC158(arg0);
    temp_v0 = func_002BC170(arg0);
    if ((temp_v0 != NULL) && (M2C_FIELD(temp_s1, s32 *, 4) == 0)) {
        temp_v1 = *temp_v0;
        if (temp_v1 != NULL) {
            temp_v1();
        }
        M2C_FIELD(temp_s1, s32 *, 4) = (s32) (M2C_FIELD(temp_s1, s32 *, 4) + 1);
    }
}
