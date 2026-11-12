#include "common.h"

u32 strlen(s8 *arg0);

void func_002FD518(s8 *arg0) {
    u32 len = strlen(arg0);
    u32 i;
    u8 c;

    for (i = 0; i < len; i++) {
        c = (u8)arg0[i];
        if (arg0[i] == 0x2F) {
            arg0[i] = 0x5C;
            c = 0x5C;
        }
        if ((u32)(c - 0x61) < 0x1A) {
            arg0[i] = c - 0x20;
        }
    }
}
