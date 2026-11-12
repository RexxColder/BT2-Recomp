#include "common.h"

void PauseMenu_Reset(void);
void func_00101A10(void);
void func_00101A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1);
extern s32 D_003B26B0 __attribute__((section(".data")));

void func_002ACE70(void) {
    s32 s0;

    func_00101A10();
    s0 = D_003B26B0;
    if (s0 == 1 || s0 == 3) {
        func_00101A60(7, 0, 0, 0, 0, 0);
    } else {
        func_00101A60(8, 0, 0, 0, 0, 0);
    }
    PauseMenu_Reset();
}
