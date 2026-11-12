#include "common.h"

s32 func_002C0178(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C0EE0(s32 arg0, s32 arg1) {
    s32 sp[8];

    func_002C0178(arg0, arg1, (s32)sp);
    return sp[1] + sp[3];
}
