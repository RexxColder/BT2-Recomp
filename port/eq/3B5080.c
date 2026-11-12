#include "m2c_macros.h"

M2C_UNK func_2B7210(s32);                           /* extern */

void func_003B5080(void *arg0) {
    if (arg0 != NULL) {
        func_2B7210(M2C_FIELD(arg0, s32 *, 0xC0));
    }
}
