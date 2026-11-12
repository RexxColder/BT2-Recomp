#include "m2c_macros.h"

void func_00129C38(void *arg0, void *arg1);

s32 func_001A4920(void *arg0, void *arg1) {
    s32 var_v0 = 0;
    u8 *temp_a0;

    if (arg0 != NULL) {
        temp_a0 = *(u8 **)((u8 *)arg0 + 0x38);
        if (temp_a0 != NULL && (*(s32 *)(temp_a0 + 0x50) & 1)) {
            func_00129C38(temp_a0 + 0x20, arg1);
            var_v0 = 1;
        }
    }
    return var_v0;
}
