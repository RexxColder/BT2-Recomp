#include "common.h"

void func_00112850(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_00112A78(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *var_s0;
    s32 temp_v1;
    s32 var_s1;

    var_s1 = 0;
    if (!(*(s32 *)arg1 & 2)) {
        var_s0 = arg1;
        do {
            temp_v1 = *(s32 *)var_s0;
            if ((temp_v1 & 1) && (var_s0[0x19] != 0)) {
                var_s1 += 1;
                if (!(temp_v1 & 4)) {
                    func_00112850(arg0, *(s16 *)(var_s0 + 0x14), arg2, arg3);
                }
            }
            var_s0 += 0x60;
        } while (!(*(s32 *)var_s0 & 2));
    }
    return var_s1;
}
