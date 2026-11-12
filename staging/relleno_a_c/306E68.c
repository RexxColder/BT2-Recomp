#include "common.h"

void func_00307028(void *fmt, s32 arg1);
extern s32 D_003A0368[2] __attribute__((section(".data")));
extern s32 D_00366460 __attribute__((section(".data")));
extern s32 D_00366464 __attribute__((section(".data")));
extern u8 D_0037FB38[] __attribute__((section(".data")));

/* 0x00306E68: "salir de sección crítica", par de BtlEvent_SetWaitOff. Si hay callback de desbloqueo
 * D_003A0368 = {fn, arg} (func_003077F0): D_00366460--; al llegar a 0, si el dueño D_00366464 no es arg0 avisa
 * con func_00307028(D_0037FB38, dueño) y lo pone a 0; después fn(arg) (siempre, llegue o no a 0).
 * Devuelve lo que deja $v0: el retorno de fn, o 0 sin callback (auto_307000.c hace `return func_00306E68(1000)`). */
s32 func_00306E68(s32 arg0) {
    if (D_003A0368[0] == 0) {
        return 0;
    }
    D_00366460 -= 1;
    if (D_00366460 == 0) {
        if (D_00366464 != arg0) {
            func_00307028(D_0037FB38, D_00366464);
        }
        D_00366464 = 0;
    }
    return ((s32 (*)(s32))D_003A0368[0])(D_003A0368[1]);
}
