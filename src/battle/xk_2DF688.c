#include "m2c_macros.h"

M2C_UNK func_002DFBC8();                     /* extern */
M2C_UNK func_003061A8();       /* extern */

s32 func_002DF688(void *arg0, void **arg1) {
    s32 sp[4];
    s32 temp_a1;
    s32 temp_s1;
    s32 temp_v1;
    s32 n;

    temp_s1 = arg0 + 0x38C;
    M2C_FIELD(*arg1, M2C_UNK (**)(void **, M2C_UNK, M2C_UNK, s32), 0x18)(arg1, 1, 0x7FFFFFFF, temp_s1);
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x38C);
    temp_a1 = temp_v1 & ~3;
    n = temp_a1 + ((s32) ((temp_v1 - temp_a1) * 8) >> 3);
    n = n + 4;
    func_003061A8(temp_s1, n - temp_v1, temp_s1, sp);
    M2C_FIELD(*arg1, M2C_UNK (**)(void **, M2C_UNK, s32), 0x20)(arg1, 0, temp_s1);
    M2C_FIELD(*arg1, M2C_UNK (**)(void **, M2C_UNK, void *), 0x1C)(arg1, 1, sp);
    func_002DFBC8(arg1);
    return 0;
}
