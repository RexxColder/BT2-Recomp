#include "common.h"

u8 *func_002BC170(s32 arg0);

s32 func_002BBAA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *obj;
    s32 (*fn)(s32, s32, s32);
    s32 ret;

    obj = func_002BC170(arg0);
    ret = 0;
    if (obj != NULL) {
        fn = *(s32 (**)(s32, s32, s32))(obj + 8);
        if (fn != NULL) {
            ret = fn(arg1, arg2, arg3);
        }
    }
    return ret;
}
