#include "common.h"

s32 func_002EE470(s32 arg0);
s32 func_0032EB50(void);
s32 func_0032EAF0(s32 arg0, s32 arg1);
extern s32 D_0034BBA0 __attribute__((section(".data")));
extern s32 D_0034BBF8 __attribute__((section(".data")));
extern s32 D_00353490 __attribute__((section(".data")));

/* 0x002EDC98: D_0034BBA0 counts down by one. When it reaches 0: func_002EE470(D_0034BBF8), v = func_0032EB50(), and
 * func_0032EAF0(v, D_00353490). Afterwards a negative counter is set to 0. */
void func_002EDC98(void) {
    s32 v;

    D_0034BBA0 = D_0034BBA0 - 1;
    if (D_0034BBA0 == 0) {
        func_002EE470(D_0034BBF8);
        v = func_0032EB50();
        func_0032EAF0(v, D_00353490);
    }
    if (D_0034BBA0 < 0) {
        D_0034BBA0 = 0;
    }
}
