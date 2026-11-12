#include "common.h"

void func_002653E8(u8 *arg0, u8 *arg1);
extern u8 *D_00387A40;

/* 0x00265920(a0): G = D_00387A40; for i < G->+0xC (at least once when it is positive): e = G->+8 + i * 0x1520;
 * when e->+0xC is nonzero and bit 1 of the word at e + 0xAF8 is set, func_002653E8(e, a0). */
void func_00265920(u8 *arg0) {
    s32 i = 0;
    s32 cnt = *(s32 *)(D_00387A40 + 0xC);
    u8 *e;

    if (cnt <= 0) {
        return;
    }
    do {
        u8 *base = *(u8 **)(D_00387A40 + 8);

        e = base + i * 0x1520;
        if (*(s32 *)(e + 0xC) != 0) {
            if ((*(s32 *)(e + 0xAF0 + 8) & 0x2) != 0) {
                func_002653E8(e, arg0);
            }
        }
        i += 1;
    } while (i < *(s32 *)(D_00387A40 + 0xC));
}
