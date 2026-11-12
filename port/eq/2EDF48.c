#include "common.h"

void func_002EE3F0();
void func_002EE470(s32 arg0);
s32 func_002EE8A8();
void func_002EF2B8();
void func_002EF868();
void func_00307998();
void func_0032EAA0();
extern s32 D_0034BBA8 __attribute__((section(".data")));
extern s64 D_0034BBD0 __attribute__((section(".data")));
extern s32 D_0034BC0C __attribute__((section(".data")));
extern s32 D_0034BC10 __attribute__((section(".data")));
extern s64 D_0034BC38 __attribute__((section(".data")));
extern s64 D_0034BC40 __attribute__((section(".data")));
extern s32 D_0034BC88 __attribute__((section(".data")));

void func_002EDF48(void) {
    if (D_0034BC38 == 0) {
        do {
            D_0034BBD0 += 1;
            func_002EE470(D_0034BC0C);
            if (D_0034BC88 == 0) {
                func_002EF868();
            }
            D_0034BC88 = 0;
            if (func_002EE8A8() == 1) {
                func_002EE470(D_0034BC10);
            }
            func_002EF2B8();
            D_0034BBA8 = 1;
            func_00307998();
            D_0034BBA8 = 0;
            func_002EE3F0();
        } while (D_0034BC38 == 0);
    }
    D_0034BC40 = 1;
    func_0032EAA0();
}
