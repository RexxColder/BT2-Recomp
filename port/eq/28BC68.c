#include "common.h"

extern s32 D_00387EB4;
extern u8 D_0038A638[] __attribute__((section(".data")));

/* 0x0028BC68: reserva `arg0` bytes (a multiplo de 16) en el SPU2 (pila de montones D_0038A638, entrada D_00387EB4: {inicio, libre}).
 * Devuelve el inicio del bloque reservado (el asm deja el inicio viejo en v0: el original lo usa como direccion del SPU). */
s32 func_0028BC68(s32 arg0) {
    s32 t = (arg0 + 0xF) & ~0xF;
    u8 *p = D_0038A638 + D_00387EB4 * 8;
    s32 start = *(s32 *)p;

    *(s32 *)p += t;
    *(s32 *)(p + 4) -= t;
    return start;
}
