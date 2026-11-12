#include "common.h"

void EftPart10_UnlinkGroup(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003877E8;

s32 func_0019B348(s32 arg0) {
    s32 *var_v1;
    s32 var_v0;

    var_v1 = *(s32 **)(D_003877E8 + 0x238);
    if (var_v1 != NULL) {
        var_v0 = *var_v1;
loop_2:
        if (var_v0 != arg0) {
            var_v1 = *(s32 **)((u8 *)var_v1 + 0xC);
            if (var_v1 != NULL) {
                var_v0 = *var_v1;
                goto loop_2;
            }
            return 0;
        }
        var_v1[0] = 0;
        var_v1[2] = 0;
        EftPart10_UnlinkGroup((s32)(D_003877E8 + 0x238), (s32)(D_003877E8 + 0x23C), (s32)var_v1);
        return 1;
    }
    return 0;
}
