#include "common.h"

s32 func_002D5060(s32 arg0, s32 arg1);

s32 func_002B5B60(s32 arg0) {
    s32 sp[4];

    if (func_002D5060(arg0, (s32)sp) == 1) {
        return sp[0];
    }
    return -1;
}
