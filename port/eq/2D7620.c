#include "common.h"

void func_002D7620(s32 unused0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 start;
    s32 end;
    s32 step;
    s32 *p;

    if (arg1 == (s32)0x80000000) {
        arg1 = 0x7FFFFFFF;
    }
    if (arg2 == (s32)0x80000000) {
        arg2 = 0x7FFFFFFF;
    }

    i = 8;
    p = (s32 *)((u8 *)arg3 + 0x20);
    do {
        i -= 1;
        *p = 0;
        p -= 1;
    } while (i >= 0);

    p = (s32 *)((u8 *)arg3 + 0x24);
    i = 7;
    do {
        i -= 1;
        *p = arg1;
        p += 1;
    } while (i >= 0);

    i = 0x11;
    if (arg1 == arg2) {
        p = (s32 *)((u8 *)arg3 + 0x44);
        do {
            i += 1;
            *p = arg1;
            p += 1;
        } while (i < 0xE0);
    } else {
        p = (s32 *)((u8 *)arg3 + 0x44);
        do {
            step = i - 0x11;
            i += 1;
            *p = (s32)((((u32)(arg2 - arg1)) / 207U) * step + arg1);
            p += 1;
        } while (i < 0xE0);
    }

    p = (s32 *)((u8 *)arg3 + 0x380);
    i = 0xF;
    do {
        i -= 1;
        *p = arg2;
        p += 1;
    } while (i >= 0);

    p = (s32 *)((u8 *)arg3 + 0x3C0);
    i = 0xF;
    do {
        i -= 1;
        *p = 0x7FFFFFFF;
        p += 1;
    } while (i >= 0);
}
