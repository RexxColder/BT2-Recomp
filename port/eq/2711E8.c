#include "common.h"

void func_00284B40(void);
void func_0028C790(void);
void sceGsSyncPath(s32 arg0, s32 arg1);
s32 sceGsSyncV(s32 arg0);
extern u8 gGfx[] __attribute__((section(".data")));

void func_002711E8(void) {
    func_00284B40();
    sceGsSyncPath(0, 0);
    func_0028C790();
    *(s32 *)(gGfx + 0x230) = sceGsSyncV(0) == 0;
    *(s32 *)(gGfx + 0x234) = *(s32 *)(gGfx + 0x234) + 1;
}
