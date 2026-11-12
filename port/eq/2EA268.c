#include "common.h"

s32 func_002EA160(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 strlen(s32 arg0);
s32 strncat(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037BAC0[] __attribute__((section(".data")));

s32 func_002EA268(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 len;
    s32 temp;

    func_002EA160(arg0, arg2, arg3, arg3);
    len = strlen(arg2);
    strncat(arg2, (s32)D_0037BAC0, (arg3 - len) - 1);
    len = strlen(arg2);
    temp = arg2 + len;
    len = strlen(arg2);
    return func_002EA160(arg1, temp, 4 - len, arg3);
}
