#include "common.h"

/* 0x0024A9D0: digit string of value (count digits, the last one is the remainder); 0xFF ends the string. */
void Num_ToDigits(u8 *digits, s32 value, s32 count, s32 zeroPad) {
    s32 pow10[8] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 };
    s32 started = 0;
    s32 n;
    s32 i;
    u32 q;
    u8 *p = digits;

    if (value == 0) {
        n = count - 1;
        for (i = 0; i < n; i++) {
            *p++ = (zeroPad != 0) ? 0 : 10;
        }
        p[0] = 0;
        p[1] = 0xFF;
        return;
    }

    n = count - 1;
    if (value < 0) {
        value = (s32)(0u - (u32)value);
    }
    for (i = n; i > 0; i--) {
        q = (u32)value / (u32)pow10[i];
        if (q == 0) {
            if (started == 0) {
                *p++ = (zeroPad == 0) ? 10 : 0;
            } else {
                *p++ = 0;
            }
        } else {
            *p++ = (u8)q;
            value = (s32)((u32)value - q * (u32)pow10[i]);
            started = 1;
        }
    }
    p[0] = (u8)value;
    p[1] = 0xFF;
}
