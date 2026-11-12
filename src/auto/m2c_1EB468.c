#include "m2c_macros.h"

M2C_UNK func_001EAD80(s32);                         /* extern */
s32 func_001EB038(s32);                             /* extern */
M2C_UNK func_001EB788(void *, void *, void *);      /* extern */

void func_001EB468(void *arg0) {
    void *temp_a0;
    void *var_s0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x38);
    var_s0 = M2C_FIELD(temp_a0, void **, 0x64);
    if (var_s0 != NULL) {
        do {
            if (func_001EB038(M2C_FIELD(var_s0, s32 *, 0)) != 0) {
                func_001EAD80(M2C_FIELD(var_s0, s32 *, 0));
            }
            M2C_FIELD(var_s0, s32 *, 4) = 0;
            func_001EB788(temp_a0 + 0x64, temp_a0 + 0x68, var_s0);
            var_s0 = M2C_FIELD(var_s0, void **, 8);
        } while (var_s0 != NULL);
    }
}
