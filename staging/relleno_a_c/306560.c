#include "common.h"

s32 func_002FD150(u8 *arg0, s32 *arg1, s32 arg2, s32 *arg3, s32 arg4);
extern s32 D_0039FEC0[] __attribute__((section(".data")));
extern s32 D_0039FFC0[] __attribute__((section(".data")));

/* 0x00306560: RPC 0x22 al IOP con 3 palabras {arg0, arg1, arg2} (en D_0039FEC0) y 1 de respuesta (en D_0039FFC0);
 * devuelve D_0039FFC0[0] (no el retorno de func_002FD150, que es el mismo valor). */
s32 func_00306560(s32 arg0, s32 arg1, s32 arg2) {
    D_0039FEC0[0] = arg0;
    D_0039FEC0[1] = arg1;
    D_0039FEC0[2] = arg2;
    func_002FD150((u8 *)0x22, D_0039FEC0, 3, D_0039FFC0, 1);
    return D_0039FFC0[0];
}
