#include "m2c_macros.h"

M2C_UNK func_0026C038(s32);                         /* extern */
M2C_UNK func_0026DF68(s32, s32, M2C_UNK);           /* extern */

void func_0026E9E8(void *arg0) {
    s32 temp_v0;
    s32 var_v1;

    var_v1 = M2C_FIELD(arg0, s32 *, 0x14);
    if (var_v1 & 0x3F8) {
        temp_v0 = var_v1 & ~0x3F8;
        M2C_FIELD(arg0, s32 *, 0x14) = temp_v0;
        var_v1 = temp_v0;
    }
    if (!(var_v1 & 1)) {
        return;
    }
    func_0026C038(M2C_FIELD(arg0, s32 *, 0x24));
    func_0026DF68(M2C_FIELD(arg0, s32 *, 0x18), M2C_FIELD(arg0, s32 *, 8), 0);
}
