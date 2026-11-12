#include "m2c_macros.h"

void func_001B0D88(void **arg0) {
    void *temp_v0;
    void *temp_v0_2;
    void *var_v1;

    temp_v0 = *arg0;
    if (temp_v0 != NULL) {
        var_v1 = temp_v0;
        do {
            temp_v0_2 = M2C_FIELD(var_v1, void **, 0x60);
            M2C_FIELD(var_v1, s32 *, 0) = 0;
            var_v1 = temp_v0_2;
        } while (temp_v0_2 != NULL);
    }
    *arg0 = NULL;
}
