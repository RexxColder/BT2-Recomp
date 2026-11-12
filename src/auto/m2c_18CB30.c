#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_0018D760(void *, void *, void *);      /* extern */

void func_0018CB30(void *arg0) {
    void *temp_s1;
    void *var_a2;
    void *var_s0;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    var_s0 = M2C_FIELD(temp_s1, void **, 0x158);
    if (var_s0 != NULL) {
        var_a2 = var_s0;
        do {
            func_0018D760(temp_s1 + 0x158, temp_s1 + 0x15C, var_a2);
            var_s0 = M2C_FIELD(var_s0, void **, 0xF4);
            var_a2 = var_s0;
        } while (var_s0 != NULL);
    }
    M2C_FIELD(temp_s1, s16 *, 0x56) = 0;
    BtlTask_SetDead(arg0);
}
