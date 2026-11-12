#include "m2c_macros.h"

M2C_UNK func_0018DCB8(s32 *, s32);                  /* extern */

void func_0018CA90(void *arg0) {
    s32 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 **, 0x38);
    if (arg0 != NULL) {
        func_0018DCB8(temp_v0, *temp_v0);
    }
}
