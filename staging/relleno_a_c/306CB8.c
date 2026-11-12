#include "common.h"

void *memset(void *dst, s32 c, u32 n);
void func_002EFAB8(void *fmt, s32 arg1);
s32 func_002FD150(u8 *arg0, s32 *arg1, s32 arg2, s32 *arg3, s32 arg4);
extern u8 D_00365900[] __attribute__((section(".data")));
extern u8 D_0037FAE0[] __attribute__((section(".data")));

/* 0x00306CB8: abre un canal en el IOP. Busca la primera de las 32 entradas de D_00365900 (0x14 bytes, byte con
 * signo +0 = en uso) libre (ninguna -> NULL); la limpia, +4 = arg0, +8 = arg1, +0xC = arg2; manda el RPC 0 con
 * {arg0, arg1, arg2, entrada} (4 palabras en la pila) y recibe 1 palabra en el mismo buffer; +0x10 = retorno.
 * Retorno 0 -> printf(D_0037FAE0) y NULL; si no, +0 = 1 y devuelve la entrada. */
u8 *func_00306CB8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    u8 *e;
    s32 i;
    s32 r;

    for (i = 0; i < 0x20; i++) {
        if (*(s8 *)(D_00365900 + i * 0x14) == 0) {
            break;
        }
    }
    if (i == 0x20) {
        return NULL;
    }
    e = D_00365900 + i * 0x14;
    memset(e, 0, 0x14);
    *(s32 *)(e + 4) = arg0;
    *(s32 *)(e + 0xC) = arg2;
    *(s32 *)(e + 8) = arg1;
    sp[0] = arg0;
    sp[1] = arg1;
    sp[2] = arg2;
    sp[3] = (s32)e;
    r = func_002FD150((u8 *)0, sp, 4, sp, 1);
    *(s32 *)(e + 0x10) = r;
    if (r == 0) {
        func_002EFAB8(D_0037FAE0, 0);
        return NULL;
    }
    *(s8 *)(e + 0) = 1;
    return e;
}
