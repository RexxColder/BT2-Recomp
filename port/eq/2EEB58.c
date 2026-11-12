#include "common.h"

void func_002EE408(s32 arg0);
void func_0032EAF0(s32 arg0, s32 arg1);
void func_0032EB90(s32 arg0);
extern s32 D_0034BC10 __attribute__((section(".data")));
extern s64 D_0034BC68 __attribute__((section(".data")));
extern s64 D_0034BC70 __attribute__((section(".data")));

void func_002EEB58(void) {
    if (D_0034BC70 == 0) {
        do {
            D_0034BC68 = 1;
            func_0032EAF0(D_0034BC10, 1);
            func_0032EB90(D_0034BC10);
            func_002EE408(D_0034BC10);
        } while (D_0034BC70 == 0);
    }
    D_0034BC70 = 0;
    D_0034BC68 = 0;
    D_0034BC10 = 0;
}
