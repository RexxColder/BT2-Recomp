#include "m2c_macros.h"

M2C_UNK func_0018B788(void *);                      /* extern */
extern s32 D_003877B4;

void func_0018BF88(void *arg0) {
    void *temp_a0;

    if (D_003877B4 != 0) {
        if (arg0 != NULL) {
            temp_a0 = M2C_FIELD(arg0, void **, 0x38);
            if ((temp_a0 != NULL) && (M2C_FIELD(temp_a0, s32 *, 0x1D8) & 2)) {
                func_0018B788(temp_a0);
            }
        }
    }
}
