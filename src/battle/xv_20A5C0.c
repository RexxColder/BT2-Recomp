#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

/* o = func_00211288(arg0) when D_00387930 is set and arg0 < 2: 1 when any of func_00211310(o, 0xC, 0x10),
 * func_00211310(o, 0xC, 0x800), func_00211310(o, 0xC, 0x80000) is nonzero; else 0 */
s32 func_0020A5C0(u32 arg0) {
    s32 o;
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        o = func_00211288(arg0);
        if (func_00211310(o, 0xC, 0x10) != 0) {
            return 1;
        }
        if (func_00211310(o, 0xC, 0x800) != 0) {
            return 1;
        }
        if (func_00211310(o, 0xC, 0x80000) != 0) {
            return 1;
        }
    }
    return 0;
}
