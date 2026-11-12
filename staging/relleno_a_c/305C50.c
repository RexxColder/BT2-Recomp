#include "common.h"

void func_003053C8(void *msg, void *fn);
extern u8 D_0037F898[] __attribute__((section(".data")));
extern u8 D_0037F8C8[] __attribute__((section(".data")));
extern u8 D_0037F988[] __attribute__((section(".data")));
extern u8 D_0037F998[] __attribute__((section(".data")));

/* 0x00305C50: añade el bloque desc = {addr, size} (2 palabras) al final de la lista arg1 (0..3) de un pool de
 * func_00305568. pool NULL / sin usar: aviso con func_003053C8 (como 305878). arg1 >= 4 (sin signo): llama al
 * callback de error pool+0x28 (si no es 0) con (pool+0x2C, -3). size <= 0 o addr == 0: no hace nada.
 * Si el pool es de tipo 1 (+5) y el último nodo de la lista termina justo en addr (+8 + +0xC == addr), lo
 * agranda (+0xC += size). Si no, toma un nodo de la lista libre (+0x14): copia las 8 bytes de desc a nodo+8
 * (ldl/ldr: desc puede no estar alineado a 8), lo saca de la libre, nodo+0 = 0 y lo encadena al final. Sin nodos
 * libres: callback de error (pool+0x2C, -3). */
void func_00305C50(u8 *pool, u32 arg1, s32 *desc) {
    u8 **link;
    u8 *last;
    u8 *node;
    s32 size;
    s32 addr;
    s32 (*cb)(s32, s32);

    if (pool == NULL) {
        func_003053C8(D_0037F988, D_0037F898);
        return;
    }
    if (*(s8 *)(pool + 4) == 0) {
        func_003053C8(D_0037F998, D_0037F8C8);
        return;
    }
    if (arg1 < 4) {
        size = desc[1];
        if (size <= 0) {
            return;
        }
        addr = desc[0];
        if (addr == 0) {
            return;
        }
        link = (u8 **)(pool + 0x18 + arg1 * 4);
        last = NULL;
        while (*link != NULL) {
            last = *link;
            link = (u8 **)last;
        }
        if (*(s8 *)(pool + 5) == 1 && last != NULL && *(s32 *)(last + 8) + *(s32 *)(last + 0xC) == addr) {
            *(s32 *)(last + 0xC) = *(s32 *)(last + 0xC) + size;
            return;
        }
        node = *(u8 **)(pool + 0x14);
        if (node != NULL) {
            u8 *next = *(u8 **)(node + 0);
            *(s32 *)(node + 8) = desc[0];
            *(s32 *)(node + 0xC) = desc[1];
            *(u8 **)(pool + 0x14) = next;
            *(u8 **)(node + 0) = NULL;
            *link = node;
            return;
        }
    }
    cb = *(s32 (**)(s32, s32))(pool + 0x28);
    if (cb != NULL) {
        cb(*(s32 *)(pool + 0x2C), -3);
    }
}
