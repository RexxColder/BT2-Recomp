#include "common.h"

void *memset(void *s, s32 c, u32 n);
extern s32 D_00355334 __attribute__((section(".data")));
extern u8 D_0039D7F8[] __attribute__((section(".data")));
extern u8 D_0039D938[] __attribute__((section(".data")));
extern u8 D_0039DB38[] __attribute__((section(".data")));

void func_002F9328(void) {
    s32 temp_v0;

    temp_v0 = D_00355334;
    if (temp_v0 == 0) {
        memset(D_0039D7F8, 0, 0x140);
        memset(D_0039D938, 0, 0x200);
        memset(D_0039DB38, 0, 9);
        D_0039DB38[0] = 0;
    }
    D_00355334 = D_00355334 + 1;
}
