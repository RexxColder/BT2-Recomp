#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002D11F0(s32 arg0);

s32 func_002D11B0(s32 arg0) {
    s32 v = func_002D11F0(arg0);

    if (v != 0) {
        func_002C2FF0(arg0, 0xFF000222);
        v = 1;
    }
    return v;
}
