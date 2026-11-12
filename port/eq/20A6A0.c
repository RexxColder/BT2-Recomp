#include "common.h"

s32 func_0020A658(s32 arg0);
s32 func_00211270(void);
extern s32 D_00387930;

s32 func_0020A6A0(void) {
    s32 i = 0;
    s32 cur;
    s32 n;

    if (D_00387930 == 0) {
        return 0;
    }
    for (;;) {
        n = func_00211270();
        cur = i;
        i++;
        if (cur >= n) {
            return 0;
        }
        if (func_0020A658(cur) != 0) {
            return 1;
        }
    }
}
