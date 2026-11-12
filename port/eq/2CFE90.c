#include "common.h"

s32 func_002C2FF0();
s32 func_002C3210();
void func_002CFD28(s32 arg0, s32 *arg1);
void func_002CFF38(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3);

s32 func_002CFE90(u8 *arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 sp[4];

    *arg2 = 0;
    *arg3 = 1;
    /* GUESS arity: a0..a3 are still the function's own params at this call */
    if (func_002C3210((s32)arg0, arg1, (s32)arg2, (s32)arg3) != 0) {
        return func_002C2FF0(0, 0xFF000157);
    }
    func_002CFD28(*(s32 *)(arg0 + 0x36B0), sp);
    if (sp[0] != 0) {
        func_002CFF38(*(s32 *)(arg0 + 0x36B0), arg1, arg2, arg3);
    }
    return 0;
}
