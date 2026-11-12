#include "common.h"

u8 *func_002A3E80(s32 arg0);
extern u8 D_003B1FF0[] __attribute__((section(".data")));

void func_002A4098(s32 arg0) {
    u8 *t;

    t = func_002A3E80(arg0);
    if ((s8)t[2] >= 0) {
        D_003B1FF0[0x4C8] = 0;
        D_003B1FF0[0x450] = 0;
        D_003B1FF0[0x478] = 0;
        D_003B1FF0[0x4A0] = 0;
    }
    if ((s8)t[3] >= 0) {
        D_003B1FF0[0x428] = 0;
        D_003B1FF0[0x400] = 0;
    }
    if ((s8)t[1] >= 0) {
        t[0xC] = 0;
    }
}
