#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_0023F4C0(s32 arg0, s32 arg1);
void func_00212690(s32 arg0, s32 arg1, s32 arg2, s32 *arg3);
extern s32 D_00387930;

s32 func_00208470(u32 arg0, s32 arg1) {
    s32 sp[4];
    s32 t;
    s32 s1;

    if (D_00387930 != 0 && arg0 < 2U) {
        t = func_00211288((s32)arg0);
        s1 = func_0023F4C0(t, arg1);
        func_00212690(t, arg1, 0, sp);
        return (s1 * 9) + sp[0];
    }
    return 0;
}
