#include "common.h"

void func_0027F2C8(u8 *arg0, u8 *arg1) {
    s32 i = 0;
    s32 t;
    u8 *a0;
    u8 v;

    do {
        t = ((i & 0xE7) | ((i & 8) * 2) | ((i & 0x10) >> 1)) * 4;
        a0 = arg0 + t;
        if (t == 0xFF) {
            a0[0] = 0;
            arg0[0x100] = 0;
            arg0[0x101] = 0;
            arg0[0x102] = 0;
        } else {
            a0[0] = 0xFF;
            a0[1] = 0xFF;
            a0[2] = 0xFF;
            v = arg1[i];
            if (v != 0x80) {
                a0[3] = v;
            } else {
                a0[3] = 0;
            }
        }
        i += 1;
    } while (i < 0x100);
}
