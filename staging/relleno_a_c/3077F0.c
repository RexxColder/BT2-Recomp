#include "common.h"

extern s32 D_003A0368[2] __attribute__((section(".data")));

/* 0x003077F0: fija el callback de desbloqueo D_003A0368 = {arg0 (fn), arg1 (arg)} de func_00306E68. */
void func_003077F0(s32 arg0, s32 arg1) {
    D_003A0368[1] = arg1;
    D_003A0368[0] = arg0;
}
