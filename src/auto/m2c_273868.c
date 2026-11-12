#include "m2c_macros.h"

M2C_UNK func_002720B8();                            /* extern */
M2C_UNK func_0028BB60(s32);                         /* extern */
extern void *D_003876A0;
extern u8 D_00387ABD;

void func_00273868(void) {
    void *temp_s0;

    if (D_00387ABD != 1) {
        temp_s0 = D_003876A0;
        if (M2C_FIELD(temp_s0, s32 *, 4) != 0) {
            func_002720B8();
            func_0028BB60(M2C_FIELD(temp_s0, s32 *, 4));
            M2C_FIELD(temp_s0, s32 *, 4) = 0;
        }
    }
}
