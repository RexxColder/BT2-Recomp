#include "common.h"

s32 Rand_Range(void *arg0, s32 arg1);
s32 func_002B4BB0(u8 *arg0, s32 arg1); /* GUESS arity: a0 = arg0 and a1 = arg1 pass through */
s32 func_002B4BE8(s32 arg0, s32 arg1);
void func_002B4D10(u8 *arg0);
extern u8 D_00378358[] __attribute__((section(".data")));

s32 func_002B4B08(u8 *arg0, s32 arg1) {
    s32 var_v0;
    s32 var_v0_2;

    if (*(s32 *)(arg0 + 0x200) >= 0x20) {
        Rand_Range(D_00378358, arg1);
        return 0;
    }
    var_v0 = 0;
    if (arg1 >= 0) {
        if (*(s32 *)(arg0 + 0x1EC) != 0) {
            var_v0_2 = func_002B4BB0(arg0, arg1);
        } else {
            var_v0_2 = func_002B4BE8(arg1, arg1);
        }
        if (var_v0_2 != 0) {
            *(s32 *)(arg0 + 0x204 + (*(s32 *)(arg0 + 0x200) * 4)) = var_v0_2;
            func_002B4D10(arg0);
        }
        var_v0 = var_v0_2;
    }
    return var_v0;
}
