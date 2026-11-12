#include "common.h"

void func_002651B8(u8 *arg0, s32 arg1, s32 arg2, f32 farg0);
extern u8 *D_00387A40;

/* 0x00265808(a0): sibling of func_00265920: G = D_00387A40; for i < G->+0xC (at least once when positive):
 * e = G->+8 + i * 0x1520; when e->+0xC is nonzero and bit 1 of the word at e + 0xAF8 is set, func_002651B8(e, a0, 1). */
void func_00265808(u8 *arg0) {
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
                func_002651B8(e, (s32)arg0, 1, 0.0f); /* f12 not set by this asm: dead/stale slot */
            }
        }
        i += 1;
    } while (i < *(s32 *)(D_00387A40 + 0xC));
}
