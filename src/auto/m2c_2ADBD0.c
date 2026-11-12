#include "m2c_macros.h"

void *func_0028BAA8(s32);                           /* extern */
M2C_UNK func_002ADA80();                            /* extern */
M2C_UNK memset(void *, M2C_UNK, s32);               /* extern */
extern void *D_00387E18;

void func_002ADBD0(s32 arg0) {
    s32 temp_s0;
    void *temp_v0;

    if ((D_00387E18 == NULL) && (arg0 > 0)) {
        temp_v0 = func_0028BAA8(0xC);
        D_00387E18 = temp_v0;
        memset(temp_v0, 0, 0xC);
        temp_s0 = arg0 * 0x1A0;
        M2C_FIELD(D_00387E18, s32 *, 4) = arg0;
        M2C_FIELD(D_00387E18, void **, 0) = func_0028BAA8(temp_s0);
        memset(M2C_FIELD(D_00387E18, void **, 0), 0, temp_s0);
        func_002ADA80();
    }
}
