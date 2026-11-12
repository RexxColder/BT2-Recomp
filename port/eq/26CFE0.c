#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);

void func_0026CFE0(void *arg0, void *arg1, void *arg2) {
    u8 *a3;
    u8 *a0;
    u8 bits;
    s32 t1;
    s32 k;
    s32 n;
    s32 take;

    a3 = (u8 *)arg0;
    bits = *(u8 *)((u8 *)arg1 + *(s32 *)arg2);
    *(s32 *)arg2 = *(s32 *)arg2 + 1;

    t1 = 0;
    for (k = 0; k < 4; k++) {
        take = (bits >> t1) & 1;
        t1 += 1;
        if (take) {
            n = *(s32 *)arg2;
            memcpy(a3, (u8 *)arg1 + n, 4);
            *(s32 *)arg2 = n + 4;
        }
        a3 += 4;
    }
    a0 = (u8 *)arg0 + 0x10;
    for (k = 0; k < 4; k++) {
        take = (bits >> t1) & 1;
        t1 += 1;
        if (take) {
            n = *(s32 *)arg2;
            a0[0] = ((u8 *)arg1)[n];
            a0[1] = ((u8 *)arg1)[n + 1];
            *(s32 *)arg2 = n + 2;
        }
        a0 += 2;
    }
}
