#include "common.h"

void func_002EE3F0(void);
s32 func_00307A10(void);
void func_0032EAA0(void);
extern s32 D_0034BBA4 __attribute__((section(".data")));
extern s32 D_0034BBB8 __attribute__((section(".data")));
extern s64 D_0034BBE8 __attribute__((section(".data")));
extern s64 D_0034BC68 __attribute__((section(".data")));
extern s64 D_0034BC70 __attribute__((section(".data")));

void func_002EE278(void) {
    s32 temp_v0;

    if (D_0034BC68 == 0) {
        do {
            D_0034BBE8 += 1;
            D_0034BBB8 = 1;
            temp_v0 = func_00307A10();
            D_0034BBB8 = 0;
            if (D_0034BBA4 == 1) {
                D_0034BBA4 = 0;
                func_002EE3F0();
            }
            if (temp_v0 == 0) {
                func_002EE3F0();
            }
        } while (D_0034BC68 == 0);
    }
    D_0034BC70 = 1;
    func_0032EAA0();
}
