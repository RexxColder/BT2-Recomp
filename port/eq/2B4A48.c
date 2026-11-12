#include "common.h"

s32 func_002B4A48(s32 arg0) {
    s32 mode = *(s32 *)(arg0 + 4);
    s32 val;

    if (mode == 0 || mode == 2) {
        return 0;
    }
    if (mode != 1) {
        return 1;
    }
    val = *(s32 *)(arg0 + 0x24);
    if (val == 0x2EE0 || val == 0 || val == 0x1770 || val == 0x5DC0 || val == 0xBB80) {
        return 1;
    }
    return 0;
}
