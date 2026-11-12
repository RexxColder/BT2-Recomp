#include "common.h"

void func_002EE3A0(s32 arg0);
void func_002EE408(s32 arg0);
void func_003070D0(s32 arg0);
void func_0032EAF0(s32 arg0, s32 arg1);
extern s32 D_0034BB70 __attribute__((section(".data")));
extern s32 D_0034BBA4 __attribute__((section(".data")));
extern s32 D_0037C4E0 __attribute__((section(".data")));

void func_002EDD08(s32 arg0, s32 arg1) {
    s32 s0;
    s32 v1;

    if (arg0 == 0) {
        return;
    }
    D_0034BBA4 = 1;
    func_0032EAF0(arg0, D_0034BB70);
    s0 = 0;
    do {
        func_002EE3A0(arg0);
        func_002EE408(arg0);
        v1 = (0x0BEBC1FF < s0);
        s0 += 1;
        if (D_0034BBA4 == 0) {
            break;
        }
        if (v1 != 0) {
            func_003070D0((s32)&D_0037C4E0);
            break;
        }
    } while (1);
    func_0032EAF0(arg0, arg1);
}
