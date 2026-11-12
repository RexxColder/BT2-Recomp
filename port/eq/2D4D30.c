#include "common.h"

s32 func_002D4D90(s32 arg0, s32 arg1);
extern u8 D_0037A858[] __attribute__((section(".data")));

s32 func_002D4D30(s32 arg0, s32 arg1, s32 arg2) {
    u8 *found;
    s32 ret;

    found = (u8 *)strstr((void *)arg0, D_0037A858);
    ret = (s32)found;
    if (found != NULL) {
        func_002D4D90(func_002D4D90((s32)(found + 4), arg1) + 1, arg2);
        ret = 1;
    }
    return ret;
}
