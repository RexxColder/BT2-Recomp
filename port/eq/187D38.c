#include "m2c_macros.h"

extern s32 D_003877B0;

s32 func_00187D38(void *arg0) {
    s32 var_v0 = 0;
    u8 *temp;
    s32 temp_v1;

    if (D_003877B0 != 0 && arg0 != NULL) {
        temp = *(u8 **)((u8 *)arg0 + 0x38);
        if (temp != NULL) {
            temp_v1 = *(s32 *)(temp + 0x19C);
            if (temp_v1 & 2) {
                *(s32 *)(temp + 0x19C) = temp_v1 | 0x200;
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
