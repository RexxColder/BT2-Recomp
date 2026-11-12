#include "common.h"

void func_001DCF70(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003878D0;

s32 func_001DCED8(s32 arg0) {
    s32 *var_v1;
    s32 var_v0;

    var_v1 = *(s32 **)(D_003878D0 + 0x120);
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
        func_001DCF70((s32)(D_003878D0 + 0x120), (s32)(D_003878D0 + 0x124), (s32)var_v1);
        return 1;
    }
    return 0;
}
