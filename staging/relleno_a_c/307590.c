#include "common.h"

void BtlFacade_BeginWait(void);
void func_00306F10(void);
void func_00307600(u32 arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x00307590: func_00307600 con los 5 argumentos (a0..a3, t0) dentro de BtlFacade_BeginWait / func_00306F10
 * (sección crítica). Tail call a func_00306F10 sin argumentos. */
void func_00307590(u32 arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    BtlFacade_BeginWait();
    func_00307600(arg0, arg1, arg2, arg3, arg4);
    func_00306F10();
}
