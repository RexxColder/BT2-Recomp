#include "common.h"

u8 *func_0010B080(void);
s32 func_0010B090(void);
s32 func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

s32 func_0010CFE0(void) {
    u8 *s0 = func_0010B080();
    s32 v = func_0010B090();
    s32 f8 = *(s32 *)(s0 + 8);

    return func_00113430(f8, v + 0x7C80, 1, 0x2A00, 0x2C80, 0, 0);
}
