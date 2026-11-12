#include "common.h"

void func_002EE3F0();
void func_003079C8();
void func_0032EAA0(void);
extern s32 D_0034BBB0;
extern s64 D_0034BBD8;
extern s64 D_0034BC48;
extern s64 D_0034BC50;
extern u16 D_0034BC84;

void func_002EE050(void) {
    if (D_0034BC48 == 0) {
loop_2:
        D_0034BBD8 += 1;
        D_0034BBB0 = 1;
        if (D_0034BC84 != 0) {
            *(s64 *)0x120000E0 = (s64)D_0034BC84;
        }
        func_003079C8();
        if (D_0034BC84 != 0) {
            *(s64 *)0x120000E0 = 0;
        }
        D_0034BBB0 = 0;
        if (D_0034BC48 == 0) {
            func_002EE3F0();
            if (D_0034BC48 == 0) {
                goto loop_2;
            }
        }
    }
    D_0034BC50 = 1;
    func_0032EAA0();
}
