#include "common.h"

extern s32 func_00277E70();
extern s32 func_0026EBC0();
extern s32 func_00249FB8();
extern s32 func_002495A8();
extern s32 func_00249778();
extern s32 func_00325830();
extern s32 func_0026EC48();
extern s32 func_0026EFC8();
extern s32 func_0026EC78();
extern s32 func_0026EEC8();
extern s32 func_0026EA58();

extern u8 *D_004279D4 __attribute__((section(".data")));
extern u8 D_00428CA0[] __attribute__((section(".data")));
extern u8 D_00428CB0[] __attribute__((section(".data")));
extern u8 D_00428CC0[] __attribute__((section(".data")));
extern u8 D_00428CD8[] __attribute__((section(".data")));
extern u8 D_00428CE8[] __attribute__((section(".data")));
extern u8 D_00428D88[] __attribute__((section(".data")));
extern u8 D_00428DA0[] __attribute__((section(".data")));
extern u8 D_00428DB8[] __attribute__((section(".data")));
extern u8 D_00428DC8[] __attribute__((section(".data")));
extern u8 D_00428DD8[] __attribute__((section(".data")));
extern u8 D_00428E18[] __attribute__((section(".data")));
extern u8 D_00428E30[] __attribute__((section(".data")));
extern u8 D_00428E40[] __attribute__((section(".data")));
extern u8 D_00428E50[] __attribute__((section(".data")));
extern u8 D_00428E68[] __attribute__((section(".data")));
extern u8 D_00428E80[] __attribute__((section(".data")));
extern u8 D_00428E90[] __attribute__((section(".data")));
extern u8 D_00428EA0[] __attribute__((section(".data")));
extern u8 D_00428EB8[] __attribute__((section(".data")));

#define G (*(u8 **)&D_004279D4)
#define W(p, o) (*(s32 *)((p) + (o)))

void func_003E8948(void) {
    u8 sp[0x170];
    s32 *r = (s32 *)(sp + 0x10);
    u8 *s4;
    u8 *g;
    s32 i, v, s1, s2;

    func_00277E70(W(G, 0x38), 0, 0x80);
    s4 = G + 0x10;
    func_0026EBC0(s4, D_00428CA0, sp);
    func_00249FB8(s4, sp, 0, 0, W(G, 8), W(G, 0xC4), 0);
    func_0026EBC0(s4, D_00428CB0, sp);
    func_002495A8(s4, sp, (s32)(G + 0xE0), 1);
    func_0026EBC0(s4, D_00428CC0, sp);
    func_00249778(s4, sp, (s32)(G + 0xE4), 3);

    for (i = 0; i < 6; i++) {
        func_00325830(sp + 0x30, D_00428CD8, i + 1);
        func_0026EBC0(s4, sp + 0x30, sp);
        r[1] = i << 5;
        r[3] = (i << 5) + 0x20;
        r[0] = 0;
        r[2] = 0x200;
        func_0026EC48(s4, sp, sp + 0x10);
        if (W(G, 0xCC) == i) {
            func_0026EFC8(s4, sp, 8);
        } else {
            func_0026EFC8(s4, sp, 4);
        }
    }

    __builtin_memcpy(sp + 0x50, D_00428CE8, 0xA0);
    for (i = 0; i < 5; i++) {
        func_0026EBC0(s4, sp + 0x50 + i * 0x20, sp);
        r[0] = 0;
        r[1] = i << 6;
        r[3] = (i << 6) + 0x40;
        r[2] = 0x40;
        g = G;
        if ((W(g, 0xC8) & 0x1F) == 0 && W(g, 0xCC) == i) {
            func_0026EC78(s4, sp, g + 0xD8, g + 0xDC, sp + 0x10, 4, 1, 6);
        } else {
            func_0026EC48(s4, sp, sp + 0x10);
        }
    }

    __builtin_memcpy(sp + 0xF0, D_00428D88, 0x18);
    __builtin_memcpy(sp + 0x110, D_00428DA0, 0x18);
    r[0] = 0;
    r[2] = 0x200;
    v = W(G, 0xCC) << 5;
    r[1] = v;
    r[3] = v + 0x20;
    func_0026EBC0(s4, D_00428DB8, sp);
    func_0026EC48(s4, sp, sp + 0x10);
    func_0026EBC0(s4, D_00428DC8, sp);
    v = W(G, 0xCC);
    func_0026EEC8(s4, sp, *(s32 *)(sp + 0xF0 + v * 4), *(s32 *)(sp + 0x110 + v * 4));
    if ((W(G, 0xC8) & 0x1F) != 0) {
        func_0026EFC8(s4, sp, 2);
    } else {
        func_0026EFC8(s4, sp, 1);
    }

    __builtin_memcpy(sp + 0x130, D_00428DD8, 0x40);
    for (i = 0; i < 2; i++) {
        r[0] = 0;
        g = G;
        v = W(g, 0xC8);
        if (v & 1) {
            r[1] = i << 6;
        } else if (v & 0x10) {
            r[1] = i ? 0x80 : 0xC0;
        } else if (W(g, 0xD4) == 0) {
            r[1] = i << 6;
        } else if (W(g, 0xD4) == 4) {
            r[1] = i ? 0x80 : 0xC0;
        }
        r[2] = r[0] + 0x100;
        r[3] = r[1] + 0x40;
        func_0026EBC0(s4, sp + 0x130 + i * 0x20, sp);
        func_0026EC48(s4, sp, sp + 0x10);
        if (W(G, 0xD0) == i) {
            func_0026EFC8(s4, sp, 8);
        } else {
            func_0026EFC8(s4, sp, 4);
        }
    }

    r[0] = 0;
    g = G;
    v = W(g, 0xC8);
    if (v & 1) {
        r[1] = W(g, 0xD0) << 6;
    } else if (v & 0x10) {
        r[1] = W(g, 0xD0) ? 0x80 : 0xC0;
    } else if (W(g, 0xD4) == 0) {
        r[1] = W(g, 0xD0) << 6;
    } else if (W(g, 0xD4) == 4) {
        r[1] = W(g, 0xD0) ? 0x80 : 0xC0;
    }
    r[2] = r[0] + 0x100;
    r[3] = r[1] + 0x40;
    func_0026EBC0(s4, D_00428E18, sp);
    func_0026EC48(s4, sp, sp + 0x10);
    func_0026EBC0(s4, D_00428E30, sp);
    func_0026EEC8(s4, sp, W(G, 0xD0) * 0xB6, 0);

    g = G;
    s1 = 0;
    if ((W(g, 0xC8) & 0xE) != 0) {
        s1 = W(g, 0xD0);
    } else {
        v = W(g, 0xD4);
        if (v == 1) {
            s1 = W(g, 0x188);
        } else if (v == 2) {
            s1 = W(g, 0x18C);
        } else if (v == 3) {
            s1 = W(g, 0x190);
        }
    }
    func_0026EBC0(s4, D_00428E40, sp);
    s2 = s1 << 5;
    func_0026EEC8(s4, sp, s2, 0);
    v = s1;
    if (s1 < 0) {
        v = s1 + 7;
    }
    v >>= 3;
    r[0] = (s1 - (v << 3)) << 4;
    r[1] = v << 5;
    r[2] = r[0] + 0x10;
    r[3] = (v << 5) + 0x20;
    func_0026EBC0(s4, D_00428E50, sp);
    func_0026EC48(s4, sp, sp + 0x10);
    func_0026EEC8(s4, sp, s2, 0);

    g = G;
    r[0] = 0;
    r[2] = 0x80;
    v = W(g, 0x184) ? 0x20 : 0;
    r[1] = v;
    r[3] = v + 0x20;
    func_0026EBC0(s4, D_00428E68, sp);
    func_0026EC48(s4, sp, sp + 0x10);

    g = G;
    r[0] = 0;
    r[2] = 0x80;
    v = (W(g, 0xE8) & 1) ? 0x60 : 0x40;
    r[1] = v;
    r[3] = v + 0x20;
    func_0026EBC0(s4, D_00428E80, sp);
    func_0026EC48(s4, sp, sp + 0x10);

    g = G;
    v = W(g, 0x188);
    r[0] = (v % 5) * 48;
    r[2] = r[0] + 0x30;
    r[1] = (W(g, 0x188) / 5) << 5;
    r[3] = r[1] + 0x20;
    func_0026EBC0(s4, D_00428E90, sp);
    func_0026EC48(s4, sp, sp + 0x10);

    g = G;
    v = W(g, 0x18C);
    r[0] = (v % 5) * 48;
    r[2] = r[0] + 0x30;
    r[1] = ((W(g, 0x18C) / 5) << 5) + 0x40;
    r[3] = r[1] + 0x20;
    func_0026EBC0(s4, D_00428EA0, sp);
    func_0026EC48(s4, sp, sp + 0x10);

    g = G;
    v = W(g, 0x190);
    r[0] = (v % 5) * 48;
    r[2] = r[0] + 0x30;
    r[1] = (W(g, 0x190) / 5) << 5;
    r[3] = r[1] + 0x20;
    func_0026EBC0(s4, D_00428EB8, sp);
    func_0026EC48(s4, sp, sp + 0x10);

    func_0026EA58(G + 0x10);
}
