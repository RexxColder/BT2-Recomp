#include "common.h"

extern u8 D_00347630[] __attribute__((section(".data")));
extern u8 *D_00347624 __attribute__((section(".data")));
extern u8 D_003477B0[] __attribute__((section(".data")));

void func_002E0108(void) {
    u8 *p;
    s32 i;

    p = D_00347630;
    for (i = 0x17F; i >= 0; i--) {
        *p++ = 0;
    }
    for (i = 0; i < 0x100; i++) {
        *p++ = (u8)i;
    }
    for (i = 0x17F; i >= 0; i--) {
        *p++ = 0xFF;
    }
    D_00347624 = D_003477B0;
}
