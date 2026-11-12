#include "m2c_macros.h"

s64 EftVram_AddTex(void *, M2C_UNK, M2C_UNK);       /* extern */
extern void *D_00387808;

void func_001A0348(void *arg0) {
    if (D_00387808 != NULL) {
        M2C_FIELD(D_00387808, s32 *, 0x334) = 0;
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 4) != 0) {
            M2C_FIELD(D_00387808, s64 *, 0x3A8) = EftVram_AddTex(D_00387808 + 0x3A8, 1, 0);
        }
    }
}
