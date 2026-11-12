#include "common.h"

void func_00128900(s32 arg0, s32 arg1) {
    u32 *d = (u32 *)arg0;
    u32 *s = (u32 *)arg1;
    s32 i;

    for (i = 0; i < 16; i++) {
        d[i] = s[i];
    }
}
