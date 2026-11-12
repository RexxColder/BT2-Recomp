#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);
s32 func_002CB0A8(s32 arg0, s32 arg1);

s32 func_002CB050(s32 arg0) {
    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF000183);
        return 0;
    }
    return func_002CB0A8(arg0, 0xFF000183) != 0;
}
