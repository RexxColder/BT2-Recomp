#include "common.h"

s32 strlen(void *s);

void func_002F9660(u8 *arg0) {
    u32 n;
    u32 i;
    u8 c;

    n = strlen(arg0) + 1;
    i = 0;
    if (n != 0) {
        do {
            i += 1;
            c = arg0[i - 1];
            if ((u32)(c - 0x61) < 0x1A) {
                arg0[i - 1] = c - 0x20;
            }
        } while (i < n);
    }
}
