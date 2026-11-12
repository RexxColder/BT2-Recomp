#include "m2c_macros.h"

M2C_UNK BtlTask_DestroyChildList(s32);              /* extern */
M2C_UNK BtlTask_Kill(s32);                          /* extern */
extern void *D_00387760;

void func_001485F8(s32 arg0) {
    s32 temp_v0;
    s32 var_s1;
    void *var_s0;

    var_s1 = 5;
    var_s0 = M2C_FIELD(D_00387760, s32 *, 4) + (arg0 * 0x270);
    do {
        temp_v0 = M2C_FIELD(var_s0, s32 *, 0x28);
        if (temp_v0 != 0) {
            BtlTask_DestroyChildList(temp_v0);
            BtlTask_Kill(M2C_FIELD(var_s0, s32 *, 0x28));
            M2C_FIELD(var_s0, s32 *, 0x28) = 0;
        }
        var_s1 -= 1;
        var_s0 += 0x50;
    } while (var_s1 >= 0);
}
