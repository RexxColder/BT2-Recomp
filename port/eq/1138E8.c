#include "common.h"

void func_001138D0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_001138E8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *s0;

    if (*(s32 *)arg0 & 2) {
        return;
    }
    s0 = arg0;
    do {
        if (*(s32 *)s0 & 1) {
            func_001138D0(s0 + 0x16, arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF, arg4 & 0xFF);
        }
        s0 += 0x60;
    } while (!(*(s32 *)s0 & 2));
}
