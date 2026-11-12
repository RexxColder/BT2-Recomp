#include "m2c_macros.h"

extern s32 D_003877B4;

s32 func_0018C068(void *arg0) {
    s32 var_v0 = 0;
    u8 *temp;
    s32 temp_v1;

    if (D_003877B4 != 0 && arg0 != NULL) {
        temp = *(u8 **)((u8 *)arg0 + 0x38);
        if (temp != NULL) {
            temp_v1 = *(s32 *)(temp + 0x1D8);
            if (temp_v1 & 2) {
                *(s32 *)(temp + 0x1D8) = temp_v1 | 0x200;
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
