#include "common.h"

extern s32 func_002C0E40(u8 *arg0, s32 arg1);
extern s32 func_002C0E10(u8 *arg0, s32 arg1, s32 arg2);
extern s32 func_002BE498(u8 *arg0);

s32 func_002BE3F0(u8 *obj) {
    u8 *p = obj + 0x1FFC;
    s32 s2 = *(s32 *)(p + 0x14);
    s32 s0 = *(s32 *)(p + 0x10);
    s32 ret;

    ret = func_002C0E40(obj, s2);
    if (ret != 1) {
        ret = func_002C0E40(obj, s0);
        if (ret == 1) {
            ret = func_002BE498(obj);
            if (ret != 0) {
                return func_002C0E10(obj, s2, 1);
            }
        }
    }
    return ret;
}
