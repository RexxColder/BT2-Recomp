#include "common.h"

void func_002EE408(s32 arg0);
void func_0032EAF0(s32 arg0, s32 arg1);
void func_0032EB90(s32 arg0);
extern s32 D_0034BC0C __attribute__((section(".data")));
extern s64 D_0034BC58 __attribute__((section(".data")));
extern s64 D_0034BC60 __attribute__((section(".data")));

void func_002EEC28(void) {
    if (D_0034BC60 == 0) {
        do {
            D_0034BC58 = 1;
            func_0032EAF0(D_0034BC0C, 1);
            func_0032EB90(D_0034BC0C);
            func_002EE408(D_0034BC0C);
        } while (D_0034BC60 == 0);
    }
    D_0034BC60 = 0;
    D_0034BC58 = 0;
    D_0034BC0C = 0;
}
