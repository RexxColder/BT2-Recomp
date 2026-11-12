#include "common.h"

extern u8 *D_0042A57C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_0042B208[] __attribute__((section(".data")));
extern u8 D_0042B218[] __attribute__((section(".data")));
extern u8 D_0042B228[] __attribute__((section(".data")));
extern u8 D_0042B238[] __attribute__((section(".data")));
extern u8 D_0042B250[] __attribute__((section(".data")));
extern u8 D_0042B260[] __attribute__((section(".data")));
extern u8 D_0042B278[] __attribute__((section(".data")));
extern u8 D_0042B288[] __attribute__((section(".data")));
extern u8 D_0042B298[] __attribute__((section(".data")));
extern u8 D_0042B2A8[] __attribute__((section(".data")));

extern s32 func_277E70();
extern s32 func_26EBC0();
extern s32 func_249778();
extern s32 func_325830();
extern s32 func_249BB8();
extern s32 func_249DB8();
extern s32 func_24A8A0();
extern s32 func_24AB10();
extern s32 func_26EFC8();
extern s32 func_26EC18();
extern s32 func_24A9D0();
extern s32 func_26EA58();

/* 0x003F89B0: level-up / result panel layout (N = D_0042A57C, W = N+0x40). Guide mouth, two name/frame pairs
 * (shown while i < N->0xC4), exp digits (N->0xBC, 5 digits), level-up text/icons from the bitmask N->0xB4 (bit 2+i),
 * two 3-digit level counters (a: current, b: after) drawn with func_24AB10, then the halo part on N+0x18 and the
 * reset loop over N+0x18+40*k. */
void func_003F89B0(void) {
    u8 sp[0x140] __attribute__((aligned(16)));
    u8 *w;
    s32 i;
    s32 j;
    s32 off;
    s32 s0;

    func_277E70(*(s32 *)(D_0042A57C + 0x68), 0, 0x80);
    w = D_0042A57C + 0x40;
    func_26EBC0(w, D_0042B208, sp);
    func_249778(w, sp, D_0042A57C + 0xD0, 1);

    for (i = 0; i < 2; i++) {
        if (i < *(s32 *)(D_0042A57C + 0xC4)) {
            s0 = *(s32 *)(D_3876A4 + 0x44 + i * 4);
            func_325830(sp + 0x10, D_0042B218, i);
            func_26EBC0(w, sp + 0x10, sp);
            func_249BB8(w, sp, 0, 0, *(s32 *)(D_0042A57C + 0x10), s0, 0);
            func_325830(sp + 0x10, D_0042B228, i);
            func_26EBC0(w, sp + 0x10, sp);
            func_249DB8(w, sp, 0, 0, *(s32 *)(D_0042A57C + 0x14), s0, 0);
        }
    }

    for (i = 0; i < 5; i++) {
        func_325830(sp + 0x30, D_0042B238, 4 - i);
        func_26EBC0(w, sp + 0x30, sp + 0x50 + i * 8);
    }
    func_24A8A0(sp + 0x80, *(s32 *)(D_0042A57C + 0xBC), 5);
    func_24AB10(w, sp + 0x50, 0, 0, *(s32 *)(D_0042A57C + 0xF0), sp + 0x80);

    if ((*(s32 *)(D_0042A57C + 0xB4) & 0xC) == 0) {
        func_26EBC0(w, D_0042B250, sp);
        func_26EFC8(w, sp, 8);
    }
    for (i = 0; i < 2; i++) {
        if ((*(s32 *)(D_0042A57C + 0xB4) & (4 << i)) == 0) {
            func_325830(sp + 0x90, D_0042B260, i);
            func_26EBC0(w, sp + 0x90, sp);
            func_26EFC8(w, sp, 8);
        }
    }
    for (i = 0; i < 2; i++) {
        func_325830(sp + 0x90, D_0042B278, i);
        func_26EBC0(w, sp + 0x90, sp);
        if ((*(s32 *)(D_0042A57C + 0xB4) & (4 << i)) != 0) {
            func_26EC18(w, sp, 1);
        } else {
            func_26EFC8(w, sp, 8);
        }
    }

    off = 0xD0;
    for (i = 0; i < 2; i++) {
        u8 *n;
        for (j = 0; j < 3; j++) {
            func_325830(sp + 0x90, D_0042B288, i, 2 - j);
            func_26EBC0(w, sp + 0x90, sp + 0xB0 + j * 8);
        }
        n = D_0042A57C;
        if (i < *(s32 *)(n + 0xC4)) {
            func_24A9D0(sp + 0xD0, *(s32 *)(n + off + 4), 3, 1);
            func_24AB10(w, sp + 0xB0, 0, 0, *(s32 *)(D_0042A57C + 0xF0), sp + 0xD0);
        } else {
            sp[0xD0] = 10;
            sp[0xD1] = 10;
            sp[0xD2] = 10;
            sp[0xD3] = 0xFF;
            func_24AB10(w, sp + 0xB0, 0, 0, *(s32 *)(n + 0xF0), sp + 0xD0);
        }
        off += 8;
    }

    *(s32 *)(sp + 0xE0) = 0xD4;
    for (i = 0; i < 2; i++) {
        u8 *n;
        for (j = 0; j < 3; j++) {
            func_325830(sp + 0x90, D_0042B298, i, 2 - j);
            func_26EBC0(w, sp + 0x90, sp + 0xB0 + j * 8);
            func_26EC18(w, sp + 0xB0 + j * 8, 1);
        }
        n = D_0042A57C;
        if ((*(s32 *)(n + 0xB4) & (4 << i)) == 0) {
            sp[0xD0] = 10;
            sp[0xD1] = 10;
            sp[0xD2] = 10;
            sp[0xD3] = 0xFF;
            func_24AB10(w, sp + 0xB0, 0, 0, *(s32 *)(n + 0xF0), sp + 0xD0);
        } else if (i < *(s32 *)(n + 0xC4)) {
            func_24A9D0(sp + 0xD0, *(s32 *)(n + *(s32 *)(sp + 0xE0) + 4), 3, 1);
            func_24AB10(w, sp + 0xB0, 0, 0, *(s32 *)(D_0042A57C + 0xF0), sp + 0xD0);
        } else {
            sp[0xD0] = 10;
            sp[0xD1] = 10;
            sp[0xD2] = 10;
            sp[0xD3] = 0xFF;
            func_24AB10(w, sp + 0xB0, 0, 0, *(s32 *)(n + 0xF0), sp + 0xD0);
        }
        *(s32 *)(sp + 0xE0) += 8;
    }

    w = D_0042A57C + 0x18;
    func_26EBC0(w, D_0042B2A8, sp);
    func_26EFC8(w, sp, 0x80);
    off = 0;
    i = 1;
    do {
        i--;
        func_26EA58(D_0042A57C + off + 0x18);
        off += 0x28;
    } while (i >= 0);
}
