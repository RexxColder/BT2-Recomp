#include "m2c_macros.h"

void *func_002BC158();                              /* extern */
void *func_002BC170(s32);                           /* extern */

void func_002BBA38(s32 arg0) {
    M2C_UNK (*temp_v0_3)(void *);
    s32 temp_v0_2;
    s32 temp_v1;
    void *temp_s1;
    void *temp_v0;

    temp_s1 = func_002BC158(arg0);
    temp_v0 = func_002BC170(arg0);
    if (temp_v0 != NULL) {
        temp_v0_2 = M2C_FIELD(temp_s1, s32 *, 4);
        temp_v1 = temp_v0_2 - 1;
        if (temp_v0_2 != 0) {
            M2C_FIELD(temp_s1, s32 *, 4) = temp_v1;
            if (temp_v1 == 0) {
                temp_v0_3 = M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 4);
                if (temp_v0_3 != NULL) {
                    temp_v0_3(temp_v0);
                }
            }
        }
    }
}
