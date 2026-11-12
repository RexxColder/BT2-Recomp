#include "common.h"

s32 func_00307B90(s32 arg0);
void func_00306F58(void);
void func_00306FD0(void);
void func_002FBCE8(s32 arg0);
void func_002FBED0(s32 arg0);
void func_002FB988(void);
extern u8 D_00355338[] __attribute__((section(".data")));
extern s32 D_00355374 __attribute__((section(".data")));
extern s32 D_00355378 __attribute__((section(".data")));
extern s32 D_0035537C __attribute__((section(".data")));
extern s32 D_003553B0 __attribute__((section(".data")));

void func_002FC0B0(void) {
    s8 s0;

    if (func_00307B90((s32)&D_00355374) != 0) {
        s0 = *(s8 *)(D_00355338 + 1);
        if (s0 == 1) {
            if (D_00355378 == s0) {
                func_00306F58();
            }
            func_002FBCE8((s32)D_00355338);
            if (D_00355378 == s0) {
                func_00306FD0();
            }
        }
        if (*(s8 *)(D_00355338 + 1) == 2) {
            if (D_0035537C == 1) {
                func_00306F58();
            }
            func_002FBED0((s32)D_00355338);
            if (D_0035537C == 1) {
                func_00306FD0();
            }
        }
        if (D_003553B0 != 0) {
            func_002FB988();
        }
        D_00355374 = 0;
    }
}
