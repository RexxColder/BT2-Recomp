#include "common.h"

void func_002ED118(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002ECAE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002ED130(void);

s32 func_002ECA70(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s0;

    func_002ED118(arg0, arg1, arg2, arg3, arg4);
    temp_s0 = func_002ECAE8(arg0, arg1, arg2, arg3, arg4);
    func_002ED130();
    return temp_s0;
}
