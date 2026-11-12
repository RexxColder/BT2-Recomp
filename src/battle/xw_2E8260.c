#include "common.h"

void func_002E81C0(s32 arg0, s32 arg1, s32 arg2);

// Forwards to func_002E81C0 with the second argument scaled as arg0 + arg1 * 2; arg2 is unused.
void func_002E8260(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002E81C0(arg0, arg0 + (arg1 * 2), arg3);
}
