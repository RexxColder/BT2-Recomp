#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_00185C68(void *, void *, void *);      /* extern */

void func_00184800(void *arg0) {
    void *temp_s1;
    void *var_a2;
    void *var_s0;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    var_s0 = M2C_FIELD(temp_s1, void **, 0x1A4);
    if (var_s0 != NULL) {
        var_a2 = var_s0;
        do {
            func_00185C68(temp_s1 + 0x1A4, temp_s1 + 0x1A8, var_a2);
            var_s0 = M2C_FIELD(var_s0, void **, 0xC0);
            var_a2 = var_s0;
        } while (var_s0 != NULL);
    }
    M2C_FIELD(temp_s1, s32 *, 0x19C) = 0;
    BtlTask_SetDead(arg0);
}
