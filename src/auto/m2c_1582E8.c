#include "m2c_macros.h"

s32 BtlScene_GetPackEntry(void *, M2C_UNK, M2C_UNK); /* extern */

s32 func_001582E8(void *arg0) {
    s32 var_a2;
    void *temp_v0;

    var_a2 = 0;
    temp_v0 = M2C_FIELD(arg0, void **, 0x1C);
    if (M2C_FIELD(temp_v0, s32 *, 0xC) != M2C_FIELD(temp_v0, s32 *, 8)) {
        var_a2 = BtlScene_GetPackEntry(temp_v0, 2, 0);
    }
    return var_a2;
}
