#include "common.h"

void func_00104CC0(s32 arg0);
void func_002A86E8(s32 arg0, s32 arg1, s32 arg2);

void func_00104E60(void) {
    s32 buf[8];

    buf[0] = 0;
    func_002A86E8((s32) buf, (s32) func_00104CC0, 0);
}
