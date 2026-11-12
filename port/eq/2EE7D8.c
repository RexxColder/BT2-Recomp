#include "common.h"

/* GUESS arity: func_0032EA60 gets the struct, the lui-only constant 0x350000, then arg1 in a2 and a3
   (a2/a3 are only arg1 on the arg0 == 0 path; after func_002EFAB8 they are whatever the callee left) */
void func_002EE278(void);
void StartThread(s32 arg0, s32 arg1);
void func_002EE470(s32 arg0);
void func_002EFAB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0032EA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0032EAF0(s32 arg0, s32 arg1);
extern u8 D_00351490[] __attribute__((section(".data")));
extern s32 D_0034BB8C __attribute__((section(".data")));
extern s32 D_0034BC0C __attribute__((section(".data")));
extern s32 D_0034BC10 __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern u8 D_0037C550[] __attribute__((section(".data")));
extern u8 D_0038BDF0[] __attribute__((section(".data")));

s32 func_002EE7D8(s32 arg0, s32 arg1) {
    s32 sp[6];

    sp[1] = (s32)func_002EE278;
    if (arg0 != 0) {
        sp[2] = arg0;
        sp[3] = arg1;
        func_002EFAB8((s32)D_0037C550, arg0, arg1, arg1);
    } else {
        sp[2] = (s32)D_00351490;
        sp[3] = 0x2000;
    }
    sp[4] = (s32)D_0038BDF0;
    sp[5] = D_00353498;
    D_0034BC10 = func_0032EA60((s32)sp, 0x350000, arg1, arg1);
    StartThread(D_0034BC10, 0);
    func_0032EAF0(D_0034BC10, D_0034BB8C);
    func_002EE470(D_0034BC10);
    return D_0034BC0C;
}
