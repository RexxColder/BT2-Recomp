#include "common.h"

void func_00305878(u8 *pool);
extern u8 D_00364AD0[] __attribute__((section(".data")));
extern u8 D_00364B08[] __attribute__((section(".data")));
extern u8 D_0037F868[] __attribute__((section(".data")));

/* 0x00305568: crea un pool de bloques. Busca la primera de las 64 entradas de D_00364B08 (0x30 bytes, byte con
 * signo +4 = en uso) libre; si no hay, devuelve NULL. La llena: +0 = &D_00364AD0, +4 = 1, +5 = (u8)arg0,
 * +8 = &D_0037F868 (nombre), +0xC = arg1 (buffer de nodos), +0x10 = arg2 / 16 (división con signo, redondeo a 0),
 * +0x28 = callback de error 0x003053A8, +0x2C = la propia entrada; llama a func_00305878 (arma la lista libre) y
 * la devuelve.
 * El callback se guarda con su dirección PS2 (0x003053A8, que en el port salta a la versión nativa por el jmp
 * de full_patch_range) para que el valor sea idéntico al original (clase "puntero de función comparado"). */
u8 *func_00305568(s32 arg0, s32 arg1, s32 arg2) {
    u8 *e;
    s32 i;

    for (i = 0; i < 0x40; i++) {
        if (*(s8 *)(D_00364B08 + i * 0x30 + 4) == 0) {
            break;
        }
    }
    if (i == 0x40) {
        return NULL;
    }
    e = D_00364B08 + i * 0x30;
    *(s8 *)(e + 4) = 1;
    *(u8 **)(e + 0) = D_00364AD0;
    *(s8 *)(e + 5) = (s8)arg0;
    *(u8 **)(e + 8) = D_0037F868;
    *(s32 *)(e + 0xC) = arg1;
    *(s32 *)(e + 0x10) = arg2 / 16;
    *(u32 *)(e + 0x28) = 0x003053A8u;
    *(u8 **)(e + 0x2C) = e;
    func_00305878(e);
    return e;
}
