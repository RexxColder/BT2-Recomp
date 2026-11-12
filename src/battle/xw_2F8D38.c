#include "common.h"

void func_002E9400(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

// Forwards to func_002E9400 with arg2 and arg1 passed through, and the addresses arg0+0x30 and arg0+0x32.
void func_002F8D38(s32 arg0, s32 arg1, s32 arg2) {
    func_002E9400(arg2, arg1, arg0 + 0x30, arg0 + 0x32);
}
