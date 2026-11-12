#include "common.h"

extern s32 *D_0039D698 __attribute__((section(".data")));

s32 func_002E1A38(s32 *arg0) {
    s32 var_v0;

    D_0039D698 = arg0;
    var_v0 = -1;
    if (arg0 != NULL) {
        var_v0 = ((*arg0 ^ 2) == 0) ? 0 : -1;
    }
    return var_v0;
}
