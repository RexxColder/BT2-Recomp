#include "common.h"

extern u8 D_0039D650[] __attribute__((section(".data")));

void func_002E15E8(void) {
    s32 n = *(s32 *)(D_0039D650 + 0x40);
    u8 *p = *(u8 **)(D_0039D650 + 0x44);
    s32 c;

    if (n > 0) {
        c = n;
        do {
            c--;
            *(s32 *)p = 1;
            p += 0x640;
        } while (c != 0);
    }
}
