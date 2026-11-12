#include "m2c_macros.h"

extern s32 D_003877BC;

s32 func_001909E8(void *arg0) {
    s32 var_v0 = 0;
    u8 *temp;
    u16 temp_v1;

    if (D_003877BC != 0 && arg0 != NULL) {
        temp = *(u8 **)((u8 *)arg0 + 0x38);
        if (temp != NULL) {
            temp_v1 = *(u16 *)(temp + 0x44);
            if (temp_v1 & 2) {
                *(u16 *)(temp + 0x44) = (u16)(temp_v1 | 0x200);
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
