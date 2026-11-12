#include "common.h"

void BtlFacade_BeginWait(void);
void func_00306F10(void);
extern s32 D_003A0320[] __attribute__((section(".data")));

/* 0x00307700: dentro de BtlFacade_BeginWait / func_00306F10: D_003A0320[arg0] = {arg1, arg2} (pares de 8 bytes,
 * índice sin comprobar). */
void func_00307700(s32 arg0, s32 arg1, s32 arg2) {
    BtlFacade_BeginWait();
    D_003A0320[arg0 * 2 + 0] = arg1;
    D_003A0320[arg0 * 2 + 1] = arg2;
    func_00306F10();
}
