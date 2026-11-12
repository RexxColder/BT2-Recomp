#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

/* when D_00387930 is set and arg0 < 2: -1 if func_00211310(o, 0xE, 0x1000) is set, else 1 if func_00211310(o, 0xE, 0x800)
 * is set (o = func_00211288(arg0)), else 0 */
s32 func_00209B08(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        s32 o = func_00211288(arg0);
        if (func_00211310(o, 0xE, 0x1000) != 0) {
            return -1;
        }
        if (func_00211310(o, 0xE, 0x800) != 0) {
            return 1;
        }
    }
    return 0;
}
