#include "common.h"

void EftAura_CommandAlt(s32 arg0, s32 arg1, s32 *arg2);
extern void *gEftGlow;

s32 func_0019A798(s32 arg0, s32 *arg2) {
    s32 *var_a2;
    s32 temp_v1;
    s32 temp_v0;

    temp_v0 = *(s32 *)(*(s32 *)((u8 *)gEftGlow + 0x6F0) + arg0 * 4);
    var_a2 = arg2;
    if (temp_v0 != 0) {
        var_a2 = *(s32 **)((u8 *)temp_v0 + 0x38);
        temp_v1 = *var_a2;
        if (!(temp_v1 & 1)) {
            return 0;
        }
        *var_a2 = temp_v1 | 4;
    }
    EftAura_CommandAlt(arg0, 2, var_a2);
    return 1;
}
