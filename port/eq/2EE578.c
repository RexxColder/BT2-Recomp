#include "common.h"

void StartThread(s32 arg0, s32 arg1);
void func_002EFAB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0032EA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0032EAF0(s32 arg0, s32 arg1);
extern void func_002EDEB0(void);
extern s32 D_0034BB78 __attribute__((section(".data")));
extern s32 D_0034BBFC __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern u8 D_0034C490[] __attribute__((section(".data")));
extern u8 D_0037C510[] __attribute__((section(".data")));
extern u8 D_0038BDF0[] __attribute__((section(".data")));

void func_002EE578(s32 arg0, s32 arg1) {
    s32 sp[6];

    sp[1] = (s32)func_002EDEB0;
    if (arg0 == 0) {
        sp[2] = (s32)D_0034C490;
        sp[3] = 0x1000;
    } else {
        sp[2] = arg0;
        sp[3] = arg1;
        func_002EFAB8((s32)D_0037C510, arg0, arg1, arg1);
    }
    sp[4] = (s32)D_0038BDF0;
    sp[5] = D_00353498;
    /* a1 is only the lui high half 0x00350000; a2/a3 are arg1 on the zero path (GUESS arity) */
    D_0034BBFC = func_0032EA60((s32)sp, 0x00350000, arg1, arg1);
    StartThread(D_0034BBFC, 0);
    func_0032EAF0(D_0034BBFC, D_0034BB78);
}
