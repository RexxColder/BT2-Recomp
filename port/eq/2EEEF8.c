#include "common.h"

void func_002EE408(s32 arg0);
void func_0032EAF0(s32 arg0, s32 arg1);
void func_0032EB90(s32 arg0);
extern s32 D_0034BBFC __attribute__((section(".data")));
extern s64 D_0034BC28 __attribute__((section(".data")));
extern s64 D_0034BC30 __attribute__((section(".data")));

void func_002EEEF8(void) {
    if (D_0034BC30 == 0) {
        do {
            D_0034BC28 = 1;
            func_0032EAF0(D_0034BBFC, 1);
            func_0032EB90(D_0034BBFC);
            func_002EE408(D_0034BBFC);
        } while (D_0034BC30 == 0);
    }
    D_0034BC30 = 0;
    D_0034BC28 = 0;
    D_0034BBFC = 0;
}
