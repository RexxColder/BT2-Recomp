#include "common.h"

s32 func_0032EB50(void);
s32 func_0032EAF0(s32 arg0, s32 arg1);
void func_002EE408(s32 arg0, s32 *arg1);
extern s32 D_0034BB70 __attribute__((section(".data")));
extern s32 D_0034BBA0 __attribute__((section(".data")));
extern s32 D_0034BBF8 __attribute__((section(".data")));
extern s32 D_00353490 __attribute__((section(".data")));
extern s32 D_00353494 __attribute__((section(".data")));

/* 0x002EDC10: on the first call (counter D_0034BBA0 == 0): s = func_0032EB50(), D_00353490 =
 * func_0032EAF0(s, D_0034BB70), D_00353494 = s, func_002EE408(D_0034BBF8, &D_00353494). Then the counter
 * (reloaded after those calls) is incremented. */
void func_002EDC10(void) {
    s32 s1v;
    s32 v;

    if (D_0034BBA0 == 0) {
        s1v = func_0032EB50();
        D_00353490 = func_0032EAF0(s1v, D_0034BB70);
        D_00353494 = s1v;
        func_002EE408(D_0034BBF8, &D_00353494);
    }
    v = D_0034BBA0;
    D_0034BBA0 = v + 1;
}
