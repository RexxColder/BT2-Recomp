#include "common.h"

void func_002FE7C8(s32 arg0, s32 *arg1);

s32 func_002FEB70(s32 arg0) {
    s32 sp[2];

    func_002FE7C8(arg0, sp);
    return sp[0] != 0;
}
