#include "common.h"

void func_001138D0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x00113980(recs, a1, a2, a3, t0, count): for each of count records (0x60 bytes) whose first word has bit 0 set,
 * func_001138D0(rec + 0x16, a1, a2, a3, t0) with the four values reduced to bytes. */
void func_00113980(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 b1 = (u8)arg1;
    u8 b2 = (u8)arg2;
    u8 b3 = (u8)arg3;
    u8 b4 = (u8)arg4;
    u8 *p = arg0;
    s32 n = arg5;

    if (n <= 0) {
        return;
    }
    do {
        if (*(s32 *)p & 1) {
            func_001138D0(p + 0x16, b1, b2, b3, b4);
        }
        n -= 1;
        p += 0x60;
    } while (n != 0);
}
