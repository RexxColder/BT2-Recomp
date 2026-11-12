#include "common.h"

void BtlFacade_BeginWait(s32 arg0);
s32 func_002FC550(s32 arg0);
s32 func_002FC7E8(s32 arg0, s32 arg1, s32 arg2);
void func_00306F10(void);
extern u8 D_00355338[] __attribute__((section(".data")));

s32 func_002FC370(void) {
    s32 sp[4];

    if (*(s8 *)(D_00355338 + 2) == 2) {
        BtlFacade_BeginWait(2);
        func_002FC550(0x2400);
        if (func_002FC7E8(*(s32 *)(D_00355338 + 0x30), 1, (s32)sp) < 0) {
            func_002FC550(0x2401);
            func_00306F10();
            return 0;
        }
        func_002FC550(0x2402);
        if (sp[0] != 0) {
            func_00306F10();
            return 1;
        }
        func_00306F10();
    }
    return 0;
}
