#include "m2c_macros.h"

M2C_UNK func_00187470(void *);                      /* extern */
extern s32 D_003877B0;

void func_00187C58(void *arg0) {
    void *temp_a0;

    if (D_003877B0 != 0) {
        if (arg0 != NULL) {
            temp_a0 = M2C_FIELD(arg0, void **, 0x38);
            if ((temp_a0 != NULL) && (M2C_FIELD(temp_a0, s32 *, 0x19C) & 2)) {
                func_00187470(temp_a0);
            }
        }
    }
}
