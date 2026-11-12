#include "common.h"

void func_003053C8(void *msg, void *fn);
extern u8 D_0037F898[] __attribute__((section(".data")));
extern u8 D_0037F8C8[] __attribute__((section(".data")));
extern u8 D_0037F928[] __attribute__((section(".data")));
extern u8 D_0037F938[] __attribute__((section(".data")));

/* 0x00305878: (re)arma la lista libre de un pool de func_00305568. pool NULL -> func_003053C8(D_0037F928,
 * D_0037F898) (aviso); pool sin usar (+4 == 0) -> func_003053C8(D_0037F938, D_0037F8C8). Si no: nodos de 16 bytes
 * desde pool+0xC, n = pool+0x10; pool+0x14 = primer nodo; los n-1 primeros: +0 = siguiente, +8 = +0xC = 0; el
 * último: +0 = +8 = +0xC = 0. Limpia las 4 cabezas pool+0x18..0x24 (el asm va de 0x24 a 0x18). */
void func_00305878(u8 *pool) {
    u8 *nodes;
    u8 *p;
    s32 i;

    if (pool == NULL) {
        func_003053C8(D_0037F928, D_0037F898);
        return;
    }
    if (*(s8 *)(pool + 4) == 0) {
        func_003053C8(D_0037F938, D_0037F8C8);
        return;
    }
    nodes = *(u8 **)(pool + 0xC);
    *(u8 **)(pool + 0x14) = nodes;
    i = 0;
    p = nodes;
    while (i < *(s32 *)(pool + 0x10) - 1) {
        *(s32 *)(p + 0xC) = 0;
        i++;
        *(s32 *)(p + 8) = 0;
        *(u8 **)(p + 0) = p + 0x10;
        p += 0x10;
    }
    p = nodes + i * 0x10;
    *(s32 *)(p + 0xC) = 0;
    *(s32 *)(p + 0) = 0;
    *(s32 *)(p + 8) = 0;
    for (i = 3; i >= 0; i--) {
        *(s32 *)(pool + 0x18 + i * 4) = 0;
    }
}
