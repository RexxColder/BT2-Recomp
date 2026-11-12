#include "common.h"

s32 func_0010B080(void);
s32 func_0010B0A0(s32 arg0);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

void func_00110AD8(s32 arg0) {
    s32 temp_s1;

    temp_s1 = func_0010B080();
    func_00113430(*(s32 *)(temp_s1 + 8), func_0010B0A0(arg0) + 0x3600, 1, 0x2A00, 0x2C80, 0, 0);
}
