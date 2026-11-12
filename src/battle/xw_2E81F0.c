#include "common.h"

void func_002E81C0(s32 arg0, s32 arg1, s32 arg2);

// Two calls to func_002E81C0 on halfword-scaled offsets of arg0: (arg0, arg0 + arg1 * 2, arg3), then
// (arg0 + arg2 * 2, arg0 + (arg2 + arg1) * 2, arg3); the second is a tail call.
void func_002E81F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002E81C0(arg0, arg0 + (arg1 * 2), arg3);
    func_002E81C0(arg0 + (arg2 * 2), arg0 + ((arg2 + arg1) * 2), arg3);
}
