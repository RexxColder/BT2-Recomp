#include "m2c_macros.h"

s32 func_001FD1A8(s32 arg0) {
    switch (arg0) {
    case 14:
    case 15:
        return 4;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 16:
    case 17:
        return 1;
    case 3:
    case 4:
    case 11:
    case 18:
    case 19:
    case 20:
        return 0;
    default:
        return 0;
    }
}
