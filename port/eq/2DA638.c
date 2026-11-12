#include "common.h"

void func_002DA638(s32 arg0, s8 arg1, u32 arg2) {
    u8 *a0;
    s32 v0;
    u32 a2;
    s32 i;

    a0 = (u8 *)(arg0 + arg2);
    v0 = arg2 & 0xF;
    if (v0 != 0) {
        do {
            a0 -= 1;
            v0 -= 1;
            *a0 = (u8)arg1;
        } while (v0 != 0);
    }
    a2 = arg2 >> 4;
    while (a2 != 0) {
        a2 -= 1;
        for (i = 0; i < 16; i++) {
            a0 -= 1;
            *a0 = (u8)arg1;
        }
    }
}
