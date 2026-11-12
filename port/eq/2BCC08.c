#include "common.h"

void func_002BD3C8(s32 arg0);
s32 func_002BCCA0(s32 arg0);
s32 func_002BCEC0(s32 arg0, s32 arg1);

s32 func_002BCC08(s32 arg0) {
    s32 a1 = 0;

    func_002BD3C8(arg0);
    if (func_002BCCA0(arg0) == 1) {
        a1 = func_002BCEC0(arg0, 0);
    }
    return a1;
}
