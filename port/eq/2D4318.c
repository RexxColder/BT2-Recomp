#include "common.h"

/* a0 passes through, a1 and a2 move to a2 and a3 */
void func_002C0DA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002D4318(s32 arg0, s32 arg1, s32 arg2) {
    func_002C0DA0(arg0, *(s32 *)(arg0 + 0x20D8), arg1, arg2);
}
