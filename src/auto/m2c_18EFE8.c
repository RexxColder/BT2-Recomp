#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_0018FC88(void *, void *, void *);      /* extern */

void func_0018EFE8(void *arg0) {
    void *temp_s1;
    void *var_a2;
    void *var_s0;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    var_s0 = M2C_FIELD(temp_s1, void **, 0x5C);
    if (var_s0 != NULL) {
        var_a2 = var_s0;
        do {
            func_0018FC88(temp_s1 + 0x5C, temp_s1 + 0x60, var_a2);
            var_s0 = M2C_FIELD(var_s0, void **, 0x100);
            var_a2 = var_s0;
        } while (var_s0 != NULL);
    }
    M2C_FIELD(temp_s1, s16 *, 0x44) = 0;
    BtlTask_SetDead(arg0);
}
