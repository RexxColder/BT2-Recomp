#include "m2c_macros.h"

M2C_UNK func_001901E0(s32 *, s32);                  /* extern */

void func_0018EF48(void *arg0) {
    s32 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 **, 0x38);
    if (arg0 != NULL) {
        func_001901E0(temp_v0, *temp_v0);
    }
}
