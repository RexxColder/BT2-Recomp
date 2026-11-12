#include "common.h"

s32 func_00282498(s32 arg0);
extern s32 D_003876A0;

s32 func_00126630(void) {
    s32 var_v0;
    s32 temp_a0;

    var_v0 = 0;
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 3) != 0) {
        var_v0 = 1;
        temp_a0 = *(s32 *)(D_003876A0 + 0xD4);
        if (temp_a0 != 3) {
            var_v0 = func_00282498(temp_a0);
            if (var_v0 != 0) {
                var_v0 = (*(u8 *)(var_v0 + 0x58) != 0);
            }
        }
    }
    return var_v0;
}
