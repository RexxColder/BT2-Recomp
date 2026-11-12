#include "common.h"

s32 StartThread(s32 arg0, s32 arg1);
s32 func_0032EA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0032EAF0(s32 arg0, s32 arg1);
extern s32 D_0034BB7C __attribute__((section(".data")));
extern s32 D_0034BC00 __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern u8 D_0038BDF0[] __attribute__((section(".data")));
extern u8 D_0034D490[] __attribute__((section(".data")));
extern u8 func_002EDF48[] __attribute__((section(".data")));

void func_002EE630(void) {
    s32 sp[12];

    sp[1] = (s32)func_002EDF48;
    sp[2] = (s32)D_0034D490;
    sp[3] = 0x1000;
    sp[4] = (s32)D_0038BDF0;
    sp[5] = D_00353498;
    D_0034BC00 = func_0032EA60((s32)sp, (s32)func_002EDF48, 0x1000, D_00353498);
    StartThread(D_0034BC00, 0);
    func_0032EAF0(D_0034BC00, D_0034BB7C);
}
