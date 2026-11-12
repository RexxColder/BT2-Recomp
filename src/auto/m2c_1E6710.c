#include "m2c_macros.h"

s32 func_001E6710(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (arg0 != NULL) {
        var_v0 = *M2C_FIELD(arg0, s32 **, 0x38);
    }
    return var_v0;
}
