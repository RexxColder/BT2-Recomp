#include "common.h"

s32 func_002BCCA0(s32 arg0);
s32 func_002BCEC0(s32 arg0, s32 arg1);

s32 func_002BCC58(s32 arg0) {
    s32 v = 0;

    if (func_002BCCA0(arg0) != 1) {
        v = func_002BCEC0(arg0, 0);
    }
    return v;
}
