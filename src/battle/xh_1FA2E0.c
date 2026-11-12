#include "m2c_macros.h"

s32 func_00211310(s32, M2C_UNK, M2C_UNK);                /* extern */

// Returns nonzero if func_00211310(arg0, 2, 2) is set.
s32 func_001FA2E0(s32 arg0) {
    return func_00211310(arg0, 2, 2) != 0;
}
