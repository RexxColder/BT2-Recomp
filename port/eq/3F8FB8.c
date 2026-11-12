#include "common.h"

extern u8 *D_0042A57C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

s32 func_26EB60(u8 *arg0);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003F8FB8: G = D_0042A57C. If func_26EB60(G+0x40) != 0 and the word at 0x003B0C34 has bit 0x4000: with P = D_3876A4,
 * if P->0x40 & 0x10004 == 0x10004: G->0xB4 |= 3 and G->0xC8 = 0xF. Otherwise also *arg0 = 0 and P->0x40 |= 0x10.
 * Both: func_297FE0(0, 1, 0x40, 0x40, 1). */
void func_003F8FB8(s32 *arg0) {
    u8 *g;
    u8 *p;

    if (func_26EB60(D_0042A57C + 0x40) == 0) {
        return;
    }
    if (!(*(s32 *)0x003B0C34 & 0x4000)) {
        return;
    }

    p = D_3876A4;
    if ((*(s32 *)(p + 0x40) & 0x10004) == 0x10004) {
        g = D_0042A57C;
        *(s32 *)(g + 0xB4) = *(s32 *)(g + 0xB4) | 1;
        g = D_0042A57C;
        *(s32 *)(g + 0xB4) = *(s32 *)(g + 0xB4) | 2;
        g = D_0042A57C;
        *(s32 *)(g + 0xC8) = 0xF;
    } else {
        g = D_0042A57C;
        *(s32 *)(g + 0xB4) = *(s32 *)(g + 0xB4) | 1;
        g = D_0042A57C;
        *(s32 *)(g + 0xB4) = *(s32 *)(g + 0xB4) | 2;
        g = D_0042A57C;
        *(s32 *)(g + 0xC8) = 0xF;
        *arg0 = 0;
        p = D_3876A4;
        *(s32 *)(p + 0x40) = *(s32 *)(p + 0x40) | 0x10;
    }

    func_297FE0(0, 1, 0x40, 0x40, 1);
}
