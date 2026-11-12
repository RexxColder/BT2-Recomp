#include "common.h"

/* 0x002411A0: a1 is the only input (a0 is overwritten before use): 1 if a1 == 3, 2 if a1 == 4, else 0. */
s32 func_002411A0(s32 arg0, s32 arg1) {
    if (arg1 == 3) {
        return 1;
    }
    if (arg1 == 4) {
        return 2;
    }
    return 0;
}
