#include "common.h"

s32 func_001E6710(s32 arg0);
void func_001E67E0(s32 arg0);

s32 func_001E7178(s32 *arg0) {
    s32 ret = 0;

    if (*arg0 != 0) {
        if (!(func_001E6710(*arg0) & 4)) {
            ret = 1;
        } else {
            func_001E67E0(*arg0);
            *arg0 = 0;
        }
    }
    return ret;
}
