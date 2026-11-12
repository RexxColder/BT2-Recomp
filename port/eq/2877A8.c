#include "common.h"

s32 OldPass_GetBit(s32 arg0);

void func_002877A8(void) {
    u8 buf[0x200];
    u8 *p = buf;
    s32 s1 = 0;

    do {
        s32 v0 = OldPass_GetBit(s1);

        s1 += 1;
        p[1] = 0xD;
        p[0] = (u8)(v0 + 0x30);
        p[2] = 0xA;
        p[3] = 0;
        p += 1;
    } while (s1 < 0xC0);
}
