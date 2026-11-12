#include "common.h"

void func_002EE408(s32 arg0);
void func_0032EAF0(s32 arg0, s32 arg1);
void func_0032EB90(s32 arg0);
extern s32 D_0034BBB0 __attribute__((section(".data")));
extern s32 D_0034BC04 __attribute__((section(".data")));
extern s64 D_0034BC48 __attribute__((section(".data")));
extern s64 D_0034BC50 __attribute__((section(".data")));
extern s32 D_0034BC8C __attribute__((section(".data")));

void func_002EEDC8(void) {
    if (D_0034BBB0 == 1) {
        while (D_0034BC50 == 0) {
        }
    } else {
        D_0034BC8C = 0;
        if (D_0034BC50 == 0) {
            do {
                D_0034BC48 = 1;
                func_0032EAF0(D_0034BC04, 1);
                func_0032EB90(D_0034BC04);
                func_002EE408(D_0034BC04);
                D_0034BC8C += 1;
            } while (D_0034BC50 == 0);
        }
    }
    D_0034BC50 = 0;
    D_0034BC48 = 0;
    D_0034BC04 = 0;
}
