#include "m2c_macros.h"

/* Returns the word at +0x34 of the sub-object at +0x1F7C, or -1 when arg0 is NULL. */
s32 func_002C3488(void *arg0) {
    void *temp_v1;

    if (arg0 == NULL) {
        return -1;
    }
    temp_v1 = M2C_FIELD(arg0, void **, 0x1F7C);
    return M2C_FIELD(temp_v1, s32 *, 0x34);
}
