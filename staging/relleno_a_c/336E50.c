#include "common.h"

s32 sceSifCallRpc(u8 *cd, s32 fno, s32 mode, s32 *send, s32 ssize, u8 *recv, s32 rsize, s32 cb, s32 cbdata);
extern s32 D_0036AB34 __attribute__((section(".data")));
extern u8 D_003AC840[] __attribute__((section(".data")));
extern s32 D_003AC880[] __attribute__((section(".data")));
extern s32 D_003AC8C0[] __attribute__((section(".data")));

/* 0x00336E50: llamada RPC de la biblioteca del IOP con un argumento. Si el estado D_0036AB34 < 0 (no
 * inicializada) devuelve 0. Si no: D_003AC8C0[0] = arg0; sceSifCallRpc(&cliente D_003AC840, función 2, modo 0,
 * D_003AC8C0, 4, D_003AC880, 4, NULL, 0 (noveno argumento en la pila)); retorno < 0 -> -1, si no D_003AC880[0]. */
s32 func_00336E50(s32 arg0) {
    if (D_0036AB34 < 0) {
        return 0;
    }
    D_003AC8C0[0] = arg0;
    if (sceSifCallRpc(D_003AC840, 2, 0, D_003AC8C0, 4, (u8 *)D_003AC880, 4, 0, 0) < 0) {
        return -1;
    }
    return D_003AC880[0];
}
