#include "m2c_macros.h"

M2C_UNK func_002FD0D8();                            /* extern */
extern s32 D_003658E4 __attribute__((section(".data")));

void func_003068A0(void) {
    s32 temp_v0;

    temp_v0 = D_003658E4 - 1;
    D_003658E4 = temp_v0;
    if (temp_v0 == 0) {
        func_002FD0D8();
    }
}
