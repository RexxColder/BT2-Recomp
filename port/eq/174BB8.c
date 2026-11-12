#include "common.h"

s32 func_00126560(s32 arg0);
s32 func_0020AA20(s32 arg0);

/* 0x00174BB8: if func_00126560(a0) != 0 return 0; otherwise return func_0020AA20(a0). */
s32 func_00174BB8(s32 arg0) {
    if (func_00126560(arg0) != 0) {
        return 0;
    }
    return func_0020AA20(arg0);
}
