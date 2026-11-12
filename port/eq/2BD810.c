#include "common.h"

s32 func_002BD810(u8 *arg0, s32 arg1, s32 *arg2) {
    *arg2 = 0x12;
    if (arg1 >= 0x12 && *arg0 == 0x80) {
        return arg0[1] == 1;
    }
    return 0;
}
