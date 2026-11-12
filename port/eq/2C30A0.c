#include "common.h"

extern u8 D_00346DC4[] __attribute__((section(".data")));
extern s32 func_002C3138(void *arg0, s32 arg1, s32 arg2);
extern s32 func_002C3210(void *arg0);
extern s32 func_002C2FF0(s32 arg0, s32 arg1);

s32 func_002C30A0(u8 *obj, s32 arg1, s32 arg2) {
    s32 ret;

    if (obj == 0) {
        ret = func_002C3138(D_00346DC4, arg1, arg2);
    } else if (func_002C3210(obj) != 0) {
        return func_002C2FF0(0, (s32)0xFF000101);
    } else {
        func_002C3138(obj + 0x9F8, arg1, arg2);
        ret = 0;
    }
    return ret;
}
