#include "common.h"

void *func_00211288(s32 arg0);
s32 func_0023D740(void *arg0, s32 arg1);
extern s32 D_00387930;

s32 func_0020C360(u32 arg0) {
    if (D_00387930 != 0 && arg0 < 2U && func_0023D740(func_00211288(arg0), 0) == 0) {
        return 1;
    }
    return 0;
}
