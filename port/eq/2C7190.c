#include "common.h"

s32 func_002C71D8(s32 arg0);

s32 func_002C7190(s32 arg0, s32 arg1, s32 arg2) {
    s32 t = arg1 < 5;
    s32 v = 1;

    if (arg2 != 0x80) {
        if (t == 0) {
            v = 0;
        } else {
            v = func_002C71D8(arg0);
            if (v != 1) {
                v = 0;
            }
        }
    }
    return v;
}
