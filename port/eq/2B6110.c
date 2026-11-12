#include "common.h"

u8 *func_002B7CB8(s32 arg0);

s32 func_002B6110(s32 arg0, s32 arg1, s32 *arg2) {
    u8 *base;
    u8 *p;
    s32 count;
    s32 i;
    s32 result;

    base = func_002B7CB8(arg0);
    count = *(s32 *)(base + 0x2520);
    p = base + 0x2528;
    i = 0;
    *arg2 = -1;
    result = 0;
    while (i < count) {
        if (arg1 == *(s32 *)(p + 8)) {
            *arg2 = i;
            result = *(s32 *)(p + 0);
        }
        i++;
        p += 0xF0;
    }
    if (*arg2 != -1) {
        return result;
    }
    return -1;
}
