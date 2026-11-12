#include "common.h"

s32 func_001AF280(s32 arg0);

s32 func_001AE4D0(void *arg0) {
    s32 temp_v1;
    s32 var_v0;

    var_v0 = 0;
    if (arg0 != NULL) {
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x38);
        if (temp_v1 != 0) {
            var_v0 = func_001AF280(temp_v1) == 0;
        }
    }
    return var_v0;
}
