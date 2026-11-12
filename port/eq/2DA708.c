#include "common.h"

void func_002DA708(s32 arg0, s32 arg1, u32 arg2) {
    s32 *p;
    u32 v1;
    u32 n;
    s32 i;

    p = (s32 *)(arg0 + arg2 * 4);
    v1 = arg2 & 0xF;
    while (v1 != 0) {
        p -= 1;
        v1 -= 1;
        *p = arg1;
    }
    n = arg2 >> 4;
    while (n != 0) {
        for (i = 0; i < 16; i++) {
            p -= 1;
            *p = arg1;
        }
        n -= 1;
    }
}
