#include "common.h"

s32 func_002D4E68(s32 arg0, s32 arg1);

s32 func_002B5D68(s32 arg0) {
    s32 sp[4];

    if (func_002D4E68(arg0, (s32)sp) == 1) {
        return sp[0];
    }
    return -1;
}
