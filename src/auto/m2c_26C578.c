#include "m2c_macros.h"

M2C_UNK func_0026C1F0(s32, s32);                    /* extern */
M2C_UNK func_0026C380(s32, s32);                    /* extern */
M2C_UNK func_0026C9F0(s32, M2C_UNK);                /* extern */
s32 func_0026CBB0(s32, M2C_UNK);                    /* extern */

void func_0026C578(void *arg0, M2C_UNK arg1, void *arg2) {
    s32 temp_v0;
    s32 temp_v1;

    func_0026C9F0(M2C_FIELD(arg2, s32 *, 0), 3);
    temp_v1 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v1 != 0) {
        func_0026C380(M2C_FIELD(arg2, s32 *, 0x24), temp_v1);
        M2C_FIELD(arg0, s32 *, 4) = 0;
    }
    temp_v0 = func_0026CBB0(M2C_FIELD(arg2, s32 *, 0), arg1);
    M2C_FIELD(arg0, s32 *, 4) = temp_v0;
    func_0026C1F0(M2C_FIELD(arg2, s32 *, 0x24), temp_v0);
}
