#include "common.h"

extern s32 D_003A0360[2] __attribute__((section(".data")));

/* 0x003077D8: fija el callback de bloqueo D_003A0360 = {arg0 (fn), arg1 (arg)} de BtlEvent_SetWaitOff. */
void func_003077D8(s32 arg0, s32 arg1) {
    D_003A0360[1] = arg1;
    D_003A0360[0] = arg0;
}
