#include "common.h"

/* the original passes a0 through (not written) and moves a1, a2 into a2, a3 */
s32 func_002C0238(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002C3368(s32 arg0, s32 arg1, s32 arg2) {
    func_002C0238(arg0, *(s32 *)(arg0 + 0x1F44), arg1, arg2);
}
