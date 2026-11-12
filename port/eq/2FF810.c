#include "common.h"

void func_002FF668(s32 arg0, s32 *arg1);

s32 func_002FF810(s32 arg0) {
    s32 sp[2];

    func_002FF668(arg0, sp);
    return sp[1] != 0;
}
