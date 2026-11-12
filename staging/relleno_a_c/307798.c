#include "common.h"

void BtlFacade_BeginWait(void);
void func_00306F10(void);
extern s32 D_003A0370[2] __attribute__((section(".data")));

/* 0x00307798: dentro de BtlFacade_BeginWait / func_00306F10 fija el callback de error D_003A0370 = {arg0 (fn),
 * arg1 (arg)} que usa func_003070D0. */
void func_00307798(s32 arg0, s32 arg1) {
    BtlFacade_BeginWait();
    D_003A0370[1] = arg1;
    D_003A0370[0] = arg0;
    func_00306F10();
}
