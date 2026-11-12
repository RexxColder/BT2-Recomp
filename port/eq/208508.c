#include "common.h"

extern s32 D_00387930;
void *func_00211288(s32 a0);
s32 func_00217488(void *a0);
s32 func_00208470(s32 a0, s32 a1);

/* jtbl_0036F9A0 maps idx 0..5 to the modes 0,1,2,0,1,2 (idx % 3). */
s32 func_00208508(s32 arg0) {
    void *p;
    s32 r;
    s32 idx;

    if (D_00387930 == 0) {
        return 0;
    }
    if ((u32)arg0 >= 2) {
        return 0;
    }
    p = func_00211288(arg0);
    r = func_00217488(p);
    idx = r - 0x34;
    if ((u32)idx >= 6) {
        return 0;
    }
    return func_00208470(arg0, idx % 3);
}
