#include "common.h"

s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0020FC88(s32 arg0);

// Calls func_002113C0 with arg0 passed through and (2, 0x100, 1), then func_0020FC88 with 0x48.
void func_00221EE8(s32 arg0) {
    func_002113C0(arg0, 2, 0x100, 1);
    func_0020FC88(0x48);
}
