#include "common.h"

s32 func_002F9280(s32 arg0, s32 arg1);
s32 func_002FD150(u8 *arg0, s32 *arg1, s32 arg2, s32 *arg3, s32 arg4);
extern s32 D_0035D220 __attribute__((section(".data")));
extern s32 D_0035D228 __attribute__((section(".data")));
extern s32 D_0035D254 __attribute__((section(".data")));
extern s32 D_0035D258 __attribute__((section(".data")));
extern s32 D_0035D260[2] __attribute__((section(".data")));
extern s32 D_0035D268 __attribute__((section(".data")));
extern u16 D_0035D27C __attribute__((section(".data")));
extern u16 D_0035D27E __attribute__((section(".data")));
extern u8 D_0037F2D8[] __attribute__((section(".data")));

/* 0x003025A0: configura la salida de sonido en el IOP. Si D_0035D228 == 1 y D_0035D220 <= 0 no hace nada.
 * func_002F9280(D_0037F2D8, &val) (lee un valor de configuración; != 0 = no está -> 48000 Hz);
 * RPC 0xC con {frecuencia, (u16)D_0035D27C, (u16)D_0035D27E} y 3 palabras de respuesta r[0..2]:
 * D_0035D268 = retorno, D_0035D260 = {r[1], r[2]}, D_0035D254 = D_0035D258 = 0.
 * Pila del original: envío en sp+0, respuesta en sp+0x10, val en sp+0x20 (buffers de 16 bytes). */
void func_003025A0(void) {
    s32 send[4];
    s32 recv[4];
    s32 val[4];

    if (D_0035D228 == 1 && D_0035D220 <= 0) {
        return;
    }
    if (func_002F9280((s32)D_0037F2D8, (s32)val) != 0) {
        send[0] = 0xBB80;
    } else {
        send[0] = val[0];
    }
    send[1] = D_0035D27C;
    send[2] = D_0035D27E;
    D_0035D268 = func_002FD150((u8 *)0xC, send, 3, recv, 3);
    D_0035D260[1] = recv[2];
    D_0035D254 = 0;
    D_0035D258 = 0;
    D_0035D260[0] = recv[1];
}
