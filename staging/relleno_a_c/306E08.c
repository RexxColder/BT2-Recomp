#include "common.h"

extern s32 D_003A0360[2] __attribute__((section(".data")));
extern s32 D_00366460 __attribute__((section(".data")));
extern s32 D_00366464 __attribute__((section(".data")));

/* 0x00306E08 BtlEvent_SetWaitOff (nombre heredado; es "entrar en sección crítica" del cliente IOP): si hay
 * callback de bloqueo D_003A0360 = {fn, arg} (lo fija func_003077D8): fn(arg); si el anidamiento D_00366460 era
 * 0 guarda el dueño D_00366464 = arg0; D_00366460++. Sin callback no hace nada.
 * Retorno: el $v0 que deja el asm (nuevo D_00366460, o &D_003A0360 sin callback); los envoltorios
 * auto_306f28.c hacen `return BtlEvent_SetWaitOff(n)`, aunque nadie debería usarlo. */
s32 BtlEvent_SetWaitOff(s32 arg0) {
    void (*fn)(s32) = (void (*)(s32))D_003A0360[0];

    if (fn == NULL) {
        return (s32)D_003A0360;
    }
    fn(D_003A0360[1]);
    if (D_00366460 == 0) {
        D_00366464 = arg0;
    }
    D_00366460 += 1;
    return D_00366460;
}
