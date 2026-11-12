#include "common.h"

void *func_00211288(s32 arg0);
s32 func_00217488(void *arg0);
extern s32 D_00387930;

s32 func_0020B378(u32 arg0) {
    if (D_00387930 != 0 && arg0 < 2U && func_00217488(func_00211288(arg0)) == 0x6F) {
        return 1;
    }
    return 0;
}
