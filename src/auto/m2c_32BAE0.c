#include "m2c_macros.h"

void _Bfree(void *arg0, void *arg1) {
    void **temp_v0;

    if (arg1 != NULL) {
        temp_v0 = (M2C_FIELD(arg1, s32 *, 4) * 4) + M2C_FIELD(arg0, s32 *, 0x4C);
        M2C_FIELD(arg1, void **, 0) = (void *) *temp_v0;
        *temp_v0 = arg1;
    }
}
