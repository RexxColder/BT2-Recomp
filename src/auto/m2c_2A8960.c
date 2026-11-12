#include "m2c_macros.h"

s32 Queue_Peek(void *arg0) {
    s32 var_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0xC);
    var_v0 = 0;
    if (temp_v1 != NULL) {
        var_v0 = M2C_FIELD(temp_v1, s32 *, 4);
    }
    return var_v0;
}
