#include "common.h"

extern s32 func_002C0E40(u8 *arg0, s32 arg1);
extern void func_002C0E10(u8 *arg0, s32 arg1, s32 arg2);
extern s32 func_002C5F60(u8 *arg0);
extern s32 func_002C6110(u8 *arg0);

s32 func_002C5EB0(u8 *obj) {
    u8 *p = obj + 0x1FB8;
    s32 s2 = *(s32 *)(p + 0x14);
    s32 s0 = *(s32 *)(p + 0x10);
    s32 ret;

    ret = func_002C0E40(obj, s2);
    if (ret != 1) {
        ret = func_002C0E40(obj, s0);
        if (ret == 1) {
            ret = func_002C5F60(obj);
            if (ret != 0) {
                func_002C0E10(obj, s2, 1);
                return func_002C6110(obj);
            }
        }
    }
    return ret;
}
