#include "common.h"

s32 StartThread(s32 arg0, s32 arg1);
s32 func_0032EA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0032EAF0(s32 arg0, s32 arg1);
extern s32 D_0034BB80 __attribute__((section(".data")));
extern s32 D_0034BC04 __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern u8 D_0038BDF0[] __attribute__((section(".data")));
extern u8 D_0034E490[] __attribute__((section(".data")));
extern u8 func_002EE050[] __attribute__((section(".data")));

void func_002EE6B8(void) {
    s32 sp[12];

    sp[1] = (s32)func_002EE050;
    sp[2] = (s32)D_0034E490;
    sp[3] = 0x1000;
    sp[4] = (s32)D_0038BDF0;
    sp[5] = D_00353498;
    D_0034BC04 = func_0032EA60((s32)sp, (s32)func_002EE050, 0x1000, D_00353498);
    StartThread(D_0034BC04, 0);
    func_0032EAF0(D_0034BC04, D_0034BB80);
}
