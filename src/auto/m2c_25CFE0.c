#include "m2c_macros.h"

void *func_0025CFE0(void **arg0) {
    void *temp_v0;
    void *var_a0;
    void *var_v1;

    var_a0 = *arg0;
    var_v1 = NULL;
    if (var_a0 != NULL) {
        do {
            var_v1 = var_a0;
            temp_v0 = M2C_FIELD(var_v1, void **, 0xDC);
            var_a0 = temp_v0;
        } while (temp_v0 != NULL);
    }
    return var_v1;
}
