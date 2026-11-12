#include "common.h"

s32 func_002C1180(s32 arg0);
s32 func_002C11A0(s32 arg0);

s32 func_002C4998(s32 arg0, s32 arg1) {
    if (arg1 == 0x80000) {
        if (func_002C1180(arg0) == 0) {
            if (func_002C11A0(arg0) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
