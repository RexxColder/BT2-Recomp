#include "common.h"

s32 func_00217488(s32 arg0);

s32 func_002125D8(s32 arg0) {
    s32 r;
    s32 ret;
    s32 want;

    r = func_00217488(arg0);
    ret = 2;
    if (r == 0x30) {
        return ret;
    }
    want = 0x31;
    if (r < 0x31) {
        ret = 0;
        if (r == 0x2E) {
            return ret;
        }
        want = 0x2F;
        ret = 1;
    } else {
        ret = 3;
    }
    if (r != want) {
        ret = -1;
    }
    return ret;
}
