#include "common.h"

s32 func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* tail call to func_00297FE0 with a fixed first argument 0x41 */
void func_0020FC88(s32 arg0) {
    func_00297FE0(0x41, arg0, 0, 0, 0);
}
