#include "common.h"

extern u8 D_00399DA8[] __attribute__((section(".data")));

void func_002E0190(void) {
    s32 n = *(s32 *)(D_00399DA8 + 0x54);
    u8 *p = *(u8 **)(D_00399DA8 + 0x58);
    s32 c;

    if (n > 0) {
        c = n;
        do {
            c--;
            *(s32 *)(p + 0x188) = 1;
            p += 0x440;
        } while (c != 0);
    }
}
