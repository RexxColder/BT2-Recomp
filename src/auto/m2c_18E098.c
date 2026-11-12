#include "m2c_macros.h"

extern s32 D_003877B8;

void func_0018E098(void *arg0) {
    u16 temp_v0;
    void *temp_a0;

    if ((D_003877B8 != 0) && (arg0 != NULL)) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if (temp_a0 != NULL) {
            temp_v0 = M2C_FIELD(temp_a0, u16 *, 0x56);
            if (temp_v0 & 2) {
                M2C_FIELD(temp_a0, u16 *, 0x56) = (u16) (temp_v0 | 4);
            }
        }
    }
}
