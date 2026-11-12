#include "m2c_macros.h"

/* Returns 1 when arg0 is NULL, else whether arg1's word at +0x38 is below arg0's. */
s32 func_002CB250(void *arg0, void *arg1) {
    s32 temp_v1;

    if (arg0 == NULL) {
        return 1;
    }
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x38);
    return M2C_FIELD(arg1, s32 *, 0x38) < temp_v1;
}
