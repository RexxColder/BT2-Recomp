#include "common.h"

void *func_00211288(s32 arg0);
s32 func_0023D4E0(void *arg0, s32 arg1);
extern s32 D_00387930;

s32 func_0020C4C0(u32 arg0) {
    if (D_00387930 != 0 && arg0 < 2U && func_0023D4E0(func_00211288(arg0), 4) == 0) {
        return 1;
    }
    return 0;
}
