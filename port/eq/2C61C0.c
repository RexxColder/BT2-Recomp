#include "common.h"

s32 func_002CABF8(s32 arg0, s32 arg1);

s32 func_002C61C0(u8 *arg0, s32 arg1) {
    s32 temp_v1;
    s32 var_v0;

    var_v0 = 0;
    if (func_002CABF8((s32)arg0, arg1) != 0) {
        var_v0 = 1;
        if (arg1 != 0) {
            temp_v1 = *(s32 *)(arg0 + 0x58);
            if ((temp_v1 != 1) || (arg1 != temp_v1) || (*(s32 *)(arg0 + 0x96C) >= *(s32 *)(arg0 + 0x968))) {
                var_v0 = 0;
            }
        }
    }
    return var_v0;
}
