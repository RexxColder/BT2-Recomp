#include "common.h"

s32 func_002CD1F8(s32 arg0);
void func_002CD2A8(s32 arg0);
s32 func_002CD5E8(s32 arg0);
void func_002CE658(s32 arg0);

s32 func_002CD138(s32 arg0) {
    s32 temp_s0;
    s32 var_s2;

    var_s2 = *(s32 *)((u8 *)arg0 + 0x48);
    temp_s0 = *(s32 *)((u8 *)arg0 + 0x4C);
    if (func_002CD1F8(arg0) != 0) {
        func_002CD2A8(arg0);
        if (temp_s0 != 3) {
            if (temp_s0 < 4) {
                if (temp_s0 != 2) {
                    return var_s2;
                }
                var_s2 = 2;
                return var_s2;
            }
            if ((temp_s0 != 4) && (temp_s0 != 6)) {
                return var_s2;
            }
            if (func_002CD5E8(arg0) != 0) {
                var_s2 = 4;
                func_002CE658(arg0);
                return var_s2;
            }
        }
        return 3;
    }
    return var_s2;
}
