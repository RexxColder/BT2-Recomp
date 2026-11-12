#include "common.h"

void sceGsSyncPath(s32 mode, s32 mask);
s32 sceGsSyncV(void);
extern u8 gGfx[] __attribute__((section(".data")));

void func_00271240(void) {
    sceGsSyncPath(0, 0);
    *(s32 *)(gGfx + 0x230) = (sceGsSyncV() == 0);
    *(s32 *)(gGfx + 0x234) = *(s32 *)(gGfx + 0x234) + 1;
}
