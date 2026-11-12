#include "common.h"

s32 func_002CD5E8(s32 arg0);
void func_002CE658(s32 arg0);

s32 func_002CD4D0(u8 *arg0) {
    s32 temp_v1;
    s32 var_s1;

    temp_v1 = *(s32 *)(arg0 + 0x4C);
    var_s1 = *(s32 *)(arg0 + 0x48);
    if (temp_v1 != 3) {
        if (temp_v1 < 4) {
            if (temp_v1 != 2) {
                return var_s1;
            }
            var_s1 = 2;
            return var_s1;
        }
        if ((temp_v1 != 4) && (temp_v1 != 6)) {
            return var_s1;
        }
        if (func_002CD5E8((s32)arg0) != 0) {
            var_s1 = 4;
            func_002CE658((s32)arg0);
        }
        return var_s1;
    }
    var_s1 = 3;
    return var_s1;
}
