#include "common.h"

s32 func_001F94A0(u8 *arg0, s32 arg1) {
    s8 *b;
    s32 sum;
    s32 i;
    s32 t;

    b = (s8 *)(arg0 + arg1 * 0x14 + 0xAF8);
    sum = 0;
    for (i = 0; i < 2; i++) {
        sum = sum + b[i] + b[i + 2] + b[i + 4] + b[i + 6] + b[i + 8];
    }
    t = sum + b[10];
    return (t < 0xB) ? t : 0xA;
}
