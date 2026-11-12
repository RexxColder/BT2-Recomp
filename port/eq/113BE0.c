#include "common.h"

void func_00113848(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00113860(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113A18(void *arg0);

void func_00113BE0(u8 *arg0, s32 arg1) {
    *(s32 *)arg0 = ((arg1 & 0xFF) == 0) ? 1 : 2;
    func_00113848(arg0 + 4, 0, 0, 0, 0);
    func_00113860(arg0 + 0xC, 0, 0, 0, 0, 0);
    func_00113A18(arg0 + 0x16);
}
