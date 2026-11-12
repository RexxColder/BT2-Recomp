#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
extern M2C_UNK D_003781D8 __attribute__((section(".data")));
extern M2C_UNK D_00378208 __attribute__((section(".data")));
extern M2C_UNK D_00378230 __attribute__((section(".data")));

s32 func_002B4488(void *arg0) {
    s32 var_a0;

    var_a0 = 1;
    if (M2C_FIELD(arg0, s32 *, 0) == 2) {
        Rand_Range(&D_003781D8);
        var_a0 = 0;
    }
    if ((u32) M2C_FIELD(arg0, u32 *, 0x24) >= 3U) {
        Rand_Range(&D_00378208);
        var_a0 = 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x10) >= 0xF) {
        Rand_Range(&D_00378230);
        var_a0 = 0;
    }
    return var_a0;
}
