#include "m2c_macros.h"

M2C_UNK EftRay_Kill(s32);                           /* extern */
extern void *D_00387920;

void func_001F46F8(void) {
    s32 temp_v0;

    if (D_00387920 != NULL) {
        temp_v0 = M2C_FIELD(D_00387920, s32 *, 0x60);
        if (temp_v0 != 0) {
            EftRay_Kill(temp_v0);
            M2C_FIELD(D_00387920, s32 *, 0x60) = 0;
        }
    }
}
