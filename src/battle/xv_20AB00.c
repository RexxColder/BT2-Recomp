#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

/* o = func_00211288(arg0) when D_00387930 is set and arg0 < 2; 1 when func_00211310(o, 1, 0x1000) is set, func_00211310(o, 1, 0x4000)
 * is clear and func_00211310(o, 1, 0x8000) is clear; else 0 */
s32 func_0020AB00(u32 arg0) {
    s32 o;
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        o = func_00211288(arg0);
        if ((func_00211310(o, 1, 0x1000) != 0) && (func_00211310(o, 1, 0x4000) == 0)) {
            return func_00211310(o, 1, 0x8000) == 0;
        }
    }
    return 0;
}
