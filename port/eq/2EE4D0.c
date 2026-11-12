#include "common.h"

s32 StartThread(s32 arg0, s32 arg1);
s32 func_002EE470(s32 arg0);
s32 func_0032EA60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_0032EAF0(s32 arg0, s32 arg1);
void func_002EDE58(void);
extern s32 D_0034BB74 __attribute__((section(".data")));
extern s32 D_0034BBF8 __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern u8 D_0038BDF0[] __attribute__((section(".data")));
extern u8 D_0034BC90[] __attribute__((section(".data")));

void func_002EE4D0(void) {
    s32 sp[12];
    s32 temp;

    temp = D_00353498;
    sp[1] = (s32)func_002EDE58;
    sp[2] = (s32)D_0034BC90;
    sp[3] = 0x800;
    sp[4] = (s32)D_0038BDF0;
    sp[5] = temp;
    D_0034BBF8 = func_0032EA60((s32)sp, (s32)func_002EDE58, 0x800, temp, (s32)D_0038BDF0, temp);
    StartThread(D_0034BBF8, 0);
    if (D_0034BBF8 != 0) {
        func_002EE470(D_0034BBF8);
    }
    func_0032EAF0(D_0034BBF8, D_0034BB74);
}
