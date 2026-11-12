#include "common.h"

s32 func_002C3210(s32 arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1);
void func_002CCC70(s32 arg0);

s32 func_002CCC28(s32 arg0) {
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000143);
    }
    func_002CCC70(arg0);
    return 0;
}
