#include "common.h"

s32 func_00217488(s32 arg0);

/* 0x00212638: v = func_00217488(arg0) - 0x34; 0 and 3 -> 0, 1 and 4 -> 1, 2 and 5 -> 2 (jump table jtbl_0036FA90),
 * anything else -> -1. */
s32 func_00212638(s32 arg0) {
    s32 v = func_00217488(arg0) - 0x34;

    switch (v) {
    case 0:
    case 3:
        return 0;
    case 1:
    case 4:
        return 1;
    case 2:
    case 5:
        return 2;
    default:
        return -1;
    }
}
