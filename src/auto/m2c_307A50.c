#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_00366468 __attribute__((section(".data")));
extern M2C_UNK D_00366488 __attribute__((section(".data")));
extern M2C_UNK D_003A0360 __attribute__((section(".data")));
extern M2C_UNK D_003A0368 __attribute__((section(".data")));
extern s32 D_003A0378 __attribute__((section(".data")));
extern M2C_UNK D_003A0380 __attribute__((section(".data")));
extern M2C_UNK D_003A0388 __attribute__((section(".data")));

void func_00307A50(void) {
    s32 *var_v1;
    s32 var_v0;

    memset(&D_00366488, 0, 0x20);
    memset(&D_003A0360, 0, 8);
    memset(&D_003A0368, 0, 8);
    memset(&D_003A0380, 0, 8);
    memset(&D_003A0388, 0, 8);
    var_v1 = &D_00366468;
    var_v0 = 5;
    do {
        var_v0 -= 1;
        *var_v1 = 0;
        var_v1 += 1;
    } while (var_v0 >= 0);
    D_003A0378 = 0;
}
