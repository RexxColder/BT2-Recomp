#include "common.h"

s32 func_002AD188(s32 arg0) {
    s32 r;

    r = 0;
    if (arg0 >= 0x21) {
        r = 2;
        if (arg0 >= 0x28E) {
            r = 4;
            if (arg0 >= 0x298) {
                r = (arg0 < 0x2FF) ? 3 : 0;
            }
        }
    }
    if (r == 2 && (arg0 - 0x21) % 3 == 0) {
        r = 1;
    }
    return r;
}
