#include "common.h"

s32 func_0032EB60(s32 arg0, s32 arg1);
s32 func_0032EB90(s32 arg0);
extern s32 D_0034BBBC __attribute__((section(".data")));
extern s32 D_0034BC08 __attribute__((section(".data")));

void func_002EF2B8(void) {
    s32 sp0;

    if (D_0034BBBC == 1) {
        func_0032EB60(D_0034BC08, (s32)&sp0);
        if (sp0 == 4 || sp0 == 0xC) {
            if (func_0032EB90(D_0034BC08) == D_0034BC08) {
                D_0034BBBC = 0;
            }
        }
    }
}
