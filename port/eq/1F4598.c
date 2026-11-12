#include "common.h"

s32 func_001F4598(u32 arg0) {
    s32 r = 0;

    if (arg0 < 0x298U) {
        r = 1;
        if (arg0 < 0x28EU) {
            r = 0;
        }
    }
    return r;
}
