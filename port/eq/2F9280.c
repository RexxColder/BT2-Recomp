#include "common.h"

s32 func_002F9170(s32 arg0, s32 arg1);
extern s32 D_0039D6EC __attribute__((section(".data")));

s32 func_002F9280(s32 arg0, s32 arg1) {
    s32 var_v0;
    s32 temp_v0;

    var_v0 = -1;
    if (D_0039D6EC != 0) {
        temp_v0 = func_002F9170(arg0, arg1);
        var_v0 = -3;
        if (temp_v0 != 0) {
            var_v0 = 0;
            *(s32 *)arg1 = *(s32 *)(temp_v0 + 0xC);
        }
    }
    return var_v0;
}
