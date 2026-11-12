#include "common.h"

void func_002EE408(s32 arg0);
void func_0032EAF0(s32 arg0, s32 arg1);
void func_0032EB90(s32 arg0);
extern s32 D_0034BC00 __attribute__((section(".data")));
extern s64 D_0034BC38 __attribute__((section(".data")));
extern s64 D_0034BC40 __attribute__((section(".data")));

void func_002EECF8(void) {
    if (D_0034BC40 == 0) {
        do {
            D_0034BC38 = 1;
            func_0032EAF0(D_0034BC00, 1);
            func_0032EB90(D_0034BC00);
            func_002EE408(D_0034BC00);
        } while (D_0034BC40 == 0);
    }
    D_0034BC40 = 0;
    D_0034BC38 = 0;
    D_0034BC00 = 0;
}
