#include "common.h"

s32 StartThread(s32 arg0, s32 arg1);
s32 func_002EE470(s32 arg0);
s32 func_0032EA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_0032EAF0(s32 arg0, s32 arg1);
extern s32 D_0034BB88 __attribute__((section(".data")));
extern s32 D_0034BC0C __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern u8 D_0034F490[] __attribute__((section(".data")));
extern u8 D_0038BDF0[] __attribute__((section(".data")));
extern u8 func_002EE140[] __attribute__((section(".data")));

void func_002EE740(void) {
    s32 sp[12];

    sp[1] = (s32)func_002EE140;
    sp[2] = (s32)D_0034F490;
    sp[3] = 0x2000;
    sp[4] = (s32)D_0038BDF0;
    sp[5] = D_00353498;
    D_0034BC0C = func_0032EA60((s32)sp, (s32)func_002EE140, 0x2000, D_00353498, (s32)D_0038BDF0, D_00353498);
    StartThread(D_0034BC0C, 0);
    func_0032EAF0(D_0034BC0C, D_0034BB88);
    func_002EE470(D_0034BC0C);
}
