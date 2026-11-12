#include "common.h"

s32 func_002BC1A0(s32 arg0);

s32 func_002BBC60(s32 arg0) {
    s32 (*fn)(s32, s32);
    void *obj;
    s32 ret;

    ret = 0;
    if (func_002BC1A0(arg0) != 1) {
        return 0;
    }
    obj = *(void **)((u8 *)arg0 + 0x8);
    if (obj != NULL) {
        fn = *(s32 (**)(s32, s32))((u8 *)obj + 0x1C);
        if (fn != NULL) {
            ret = fn(*(s32 *)((u8 *)arg0 + 0x1C), 0);
        }
    }
    return ret;
}
