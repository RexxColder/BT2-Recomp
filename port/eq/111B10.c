#include "common.h"

u8 *func_0010B080(void);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

void func_00111B10(s32 arg0) {
    u8 *p = func_0010B080();
    func_00113430(*(s32 *)(p + 4), arg0, 1, 0x2A00, 0x2C00, 0, 0);
}
