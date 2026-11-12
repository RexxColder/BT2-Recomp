#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);
void func_002CCFB0(s32 arg0, s32 arg1);

s32 func_002CCF00(s32 arg0) {
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000138);
    }
    func_002CCFB0(arg0, 0xFF000138);
    return 0;
}
