#include "common.h"

void func_002DDD70(s32 arg0, s32 arg1);
s32 func_002DFBC8(s32 arg0);
s32 func_002DFDF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E0750(s32 arg0, s32 arg1);

void func_002DDF68(s32 arg0, s32 arg1) {
    s32 var_s1;
    s32 temp_v0;

    if (func_002E0750(arg0, arg1) != 0) {
        func_002DDD70(0, 0xFF03020A);
        return;
    }
    var_s1 = 0xFF030305;
    for (;;) {
        temp_v0 = func_002DFBC8(arg1);
        if (temp_v0 != 0) {
            if ((temp_v0 & 0xCC) != 0) {
                var_s1 = 0;
            } else if (func_002DFDF0(arg1, 1, 4) == 4) {
                continue;
            }
        }
        break;
    }
    func_002DDD70(arg0, var_s1);
}
