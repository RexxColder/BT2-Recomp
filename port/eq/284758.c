#include "common.h"

void func_00284758(u8 *arg0) {
    s32 i;
    s32 off;
    u8 *p;

    arg0[0] = 0;
    arg0[1] = 0;
    arg0[2] = 0;
    arg0[3] = 0;
    for (i = 0; i < 0x100; i++) {
        off = ((i & 0xE7) | ((i & 8) << 1) | ((i & 0x10) >> 1)) * 4;
        p = arg0 + off;
        if (i != 0xFF) {
            p[0] = 0;
            p[1] = 0;
            p[2] = 0;
            p[3] = 0;
        } else {
            p[0] = 0x40;
            p[1] = 0x40;
            p[2] = 0x40;
            p[3] = 0x40;
        }
    }
}
