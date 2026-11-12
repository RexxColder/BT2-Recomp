#include "common.h"

void *func_002B61E0(void);

s32 func_002B43E0(s32 arg0) {
    u8 *temp_a1;
    s32 var_a0 = 0;

    temp_a1 = (u8 *)func_002B61E0();
    if (*(s32 *)((u8 *)arg0 + 0x18) == 0) {
        var_a0 = (*(s32 *)(temp_a1 + 0x2C) == 0) ? -1 : ((*(s32 *)(temp_a1 + 0x28) != 0) ? 0 : -1);
    }
    return var_a0;
}
