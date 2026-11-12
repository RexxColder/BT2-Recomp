#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0, s32 arg1);
s32 func_002D07B0(s32 arg0, s32 arg1);

s32 func_002BF380(s32 arg0, s32 arg1) {
    s32 ret;
    s32 vt;
    s32 fn;

    if (func_002C3210(arg0, arg1) != 0) {
        func_002C2FF0(0, 0xFF0001A2);
        return 0;
    }
    ret = func_002D07B0(arg0, 6);
    if (ret != 0) {
        vt = *(s32 *)(arg0 + 0x2114);
        fn = *(s32 *)(vt + 8);
        ret = ((s32 (*)(s32, s32))fn)(arg0, arg1);
    }
    return ret;
}
