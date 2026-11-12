#include "common.h"

s32 func_002EA5F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002EAFE0(s32 arg0);
void func_002EA3A0(void);
void func_002EF218(void);

s32 func_002EA508(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v1;

    temp_v0 = func_002EA5F0(arg0, arg1, arg2, arg3);
    if (temp_v0 < 0) {
        return temp_v0;
    }
    for (;;) {
        temp_v0_2 = func_002EAFE0(arg0);
        var_v1 = 0;
        if (temp_v0_2 != 3) {
            var_v1 = -1;
            if (temp_v0_2 == 4) {
                return var_v1;
            }
            func_002EF218();
            func_002EA3A0();
            continue;
        }
        return var_v1;
    }
}
