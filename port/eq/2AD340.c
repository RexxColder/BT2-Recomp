#include "common.h"

void func_002AD1F0(s32 arg0, s32 arg1, s32 arg2);

s32 func_002AD340(s32 arg0) {
    s32 out;

    func_002AD1F0(arg0, (s32)&out, 0);
    return out;
}
