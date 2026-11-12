#include "common.h"

void func_00307980(void);
void func_002EE3F0(void);
void func_0032EAA0(void);
extern s32 D_0034BBAC __attribute__((section(".data")));
extern s64 D_0034BBC8 __attribute__((section(".data")));
extern s64 D_0034BC28 __attribute__((section(".data")));
extern s64 D_0034BC30 __attribute__((section(".data")));

void func_002EDEB0(void) {
    if (D_0034BC28 == 0) {
        do {
            D_0034BBC8 += 1;
            D_0034BBAC = 1;
            func_00307980();
            D_0034BBAC = 0;
            func_002EE3F0();
        } while (D_0034BC28 == 0);
    }
    D_0034BC30 = 1;
    func_0032EAA0();
}
