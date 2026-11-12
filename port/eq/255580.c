#include "common.h"

/* 0x00255580: input handler of a menu screen (state at menu+0x16C: 0 = choose entry, 1 = choose slot,
 * 2 = confirmation yes/no, 3 = rules prompt). Reads the pad edge words of D_003B0B00 (+0x144 directions,
 * +0x134 buttons: 0x4000 = confirm, 0x1000 = cancel), moves cursors, edits the entry tables and plays a sound.
 * Returns the sound call result, or an approximation of the stale v0 when no input is acted on. */
extern u8 *D_003879D0;
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_003761F0[];
extern u8 D_00376208[];
extern u8 D_00376228[];
extern u8 D_003879D8[];
extern u8 D_003879E0[];

s32 func_0026EB60(u8 *p);
void func_0026EB78(u8 *p, u8 *name);
s32 func_00254138(s32 a);
void func_002541B0(void);
void func_00253BE8(void);
void func_00253E50(s32 a);
void func_0026EAE0(u8 *p, s32 n);
void func_0026EA88(u8 *p);
s32 func_00297FE0(s32 a, s32 b, s32 c, s32 d, s32 e);

#define MENU_ENTRY(g, i) ((g) + (i) * 20 + 0x1A0)

s32 func_00255580(void) {
    u8 *g;
    s32 state;
    s32 dir;
    s32 btn;
    s32 cur;
    s32 first;
    s32 cursor;

    if (func_0026EB60(D_003879D0 + 0x28) == 0) {
        return 0;
    }
    g = D_003879D0;
    state = *(s32 *)(g + 0x16C);

    if (state == 1) {
        dir = *(s32 *)(D_003B0B00 + 0x144);
        if (dir & 0x80) {
            if (*(s32 *)(g + 0x19C) < 2) {
                return 1;
            }
            first = *(s32 *)(g + 0x160);
            do {
                *(s32 *)(g + 0x160) = *(s32 *)(g + 0x160) - 1;
                g = D_003879D0;
                if (*(s32 *)(g + 0x160) < 0) {
                    *(s32 *)(g + 0x160) = *(s32 *)(g + 0x19C) - 1;
                    g = D_003879D0;
                }
                cursor = *(s32 *)(g + 0x160);
            } while (*(s32 *)(g + 0x178 + cursor * 8) == 0x85);
            if (first == cursor) {
                return (s32)(g + cursor * 8);
            }
            func_002541B0();
            func_00254138(0);
            return func_00297FE0(0, 8, 64, 64, 1);
        }
        if (dir & 0x20) {
            if (*(s32 *)(g + 0x19C) < 2) {
                return 1;
            }
            first = *(s32 *)(g + 0x160);
            do {
                *(s32 *)(g + 0x160) = *(s32 *)(g + 0x160) + 1;
                g = D_003879D0;
                if (*(s32 *)(g + 0x19C) - 1 < *(s32 *)(g + 0x160)) {
                    *(s32 *)(g + 0x160) = 0;
                    g = D_003879D0;
                }
                cursor = *(s32 *)(g + 0x160);
            } while (*(s32 *)(g + 0x178 + cursor * 8) == 0x85);
            if (first == cursor) {
                return (s32)(g + cursor * 8);
            }
            func_002541B0();
            func_00254138(0);
            return func_00297FE0(0, 8, 64, 64, 1);
        }
        btn = *(s32 *)(D_003B0B00 + 0x134);
        if (btn & 0x4000) {
            *(s32 *)(g + 0x178 + *(s32 *)(g + 0x160) * 8) = 0x85;
            *(s32 *)(MENU_ENTRY(D_003879D0, *(s32 *)(D_003879D0 + 0x168)) + 0x10) = *(s32 *)(D_003879D0 + 0x160);
            *(s32 *)(D_003879D0 + 0x270) = *(s32 *)(D_003879D0 + 0x270) + 1;
            func_0026EB78(D_003879D0 + 0x50, D_003879D8);
            *(s32 *)(D_003879D0 + 0x16C) = 0;
            return func_00297FE0(0, 1, 64, 64, 1);
        }
        if (btn & 0x1000) {
            func_00253E50(*(s32 *)(g + 0x168));
            *(s32 *)(D_003879D0 + 0x15C) |= 0x200;
            func_0026EB78(D_003879D0 + 0x50, D_003879D8);
            *(s32 *)(D_003879D0 + 0x16C) = 0;
            return func_00297FE0(0, 2, 64, 64, 1);
        }
        return 0;
    }

    if (state < 2) {
        if (state != 0) {
            return 1;
        }
        dir = *(s32 *)(D_003B0B00 + 0x144);
        if (dir & 0x90) {
            if (*(s32 *)(g + 0x268) < 2) {
                return 1;
            }
            *(s32 *)(g + 0x168) = *(s32 *)(g + 0x168) - 1;
            g = D_003879D0;
            if (*(s32 *)(g + 0x168) < 0) {
                *(s32 *)(g + 0x168) = *(s32 *)(g + 0x268) - 1;
                g = D_003879D0;
            }
            if (*(s32 *)MENU_ENTRY(g, *(s32 *)(g + 0x168)) >= 0) {
                func_00254138(0);
            } else {
                *(s32 *)(g + 0x15C) |= 0x200;
            }
            return func_00297FE0(0, 0, 64, 64, 1);
        }
        if (dir & 0x60) {
            if (*(s32 *)(g + 0x268) < 2) {
                return 1;
            }
            *(s32 *)(g + 0x168) = *(s32 *)(g + 0x168) + 1;
            g = D_003879D0;
            if (*(s32 *)(g + 0x268) - 1 < *(s32 *)(g + 0x168)) {
                *(s32 *)(g + 0x168) = 0;
                g = D_003879D0;
            }
            if (*(s32 *)MENU_ENTRY(g, *(s32 *)(g + 0x168)) >= 0) {
                func_00254138(0);
            } else {
                *(s32 *)(g + 0x15C) |= 0x200;
            }
            return func_00297FE0(0, 0, 64, 64, 1);
        }
        btn = *(s32 *)(D_003B0B00 + 0x134);
        if (btn & 0x4000) {
            if (*(s32 *)MENU_ENTRY(g, *(s32 *)(g + 0x168)) >= 0) {
                if (*(s32 *)(g + 0x268) == *(s32 *)(g + 0x270)) {
                    *(s32 *)(g + 0x164) = 1;
                    g = D_003879D0;
                }
                func_0026EB78(g + 0x28, D_003761F0);
                *(s32 *)(D_003879D0 + 0x16C) = 2;
            } else {
                if (*(s32 *)(g + 0x178 + *(s32 *)(g + 0x160) * 8) == 0x85) {
                    do {
                        *(s32 *)(g + 0x160) = *(s32 *)(g + 0x160) + 1;
                        g = D_003879D0;
                        if (*(s32 *)(g + 0x19C) - 1 < *(s32 *)(g + 0x160)) {
                            *(s32 *)(g + 0x160) = 0;
                            g = D_003879D0;
                        }
                    } while (*(s32 *)(g + 0x178 + *(s32 *)(g + 0x160) * 8) == 0x85);
                }
                func_00253BE8();
                func_0026EAE0(D_003879D0 + 0x50, 0x3C);
                func_0026EA88(D_003879D0 + 0x50);
                func_002541B0();
                *(s32 *)(D_003879D0 + 0x16C) = 1;
                func_00254138(0);
            }
            return func_00297FE0(0, 1, 64, 64, 1);
        }
        if (btn & 0x1000) {
            if (*(s32 *)(g + 0x19C) == 1) {
                return func_00297FE0(0, 7, 64, 64, 1);
            }
            cur = *(s32 *)(g + 0x168);
            if (*(s32 *)MENU_ENTRY(g, cur) >= 0) {
                u8 *p = g + 0x170 + *(s32 *)(MENU_ENTRY(g, cur) + 0x10) * 8;

                *(s32 *)(p + 8) = *(s32 *)(p + 4);
                *(s32 *)(D_003879D0 + 0x270) = *(s32 *)(D_003879D0 + 0x270) - 1;
                func_00253E50(*(s32 *)(D_003879D0 + 0x168));
                *(s32 *)(D_003879D0 + 0x15C) |= 0x200;
                return func_00297FE0(0, 2, 64, 64, 1);
            }
            return func_00297FE0(0, 7, 64, 64, 1);
        }
        return 0;
    }

    if (state == 2) {
        dir = *(s32 *)(D_003B0B00 + 0x144);
        if (dir & 0x10) {
            *(s32 *)(g + 0x164) = *(s32 *)(g + 0x164) - 1;
            if (*(s32 *)(D_003879D0 + 0x164) < 0) {
                *(s32 *)(D_003879D0 + 0x164) = 1;
            }
            return func_00297FE0(0, 0, 64, 64, 1);
        }
        if (dir & 0x40) {
            *(s32 *)(g + 0x164) = *(s32 *)(g + 0x164) + 1;
            if (*(s32 *)(D_003879D0 + 0x164) >= 2) {
                *(s32 *)(D_003879D0 + 0x164) = 0;
            }
            return func_00297FE0(0, 0, 64, 64, 1);
        }
        btn = *(s32 *)(D_003B0B00 + 0x134);
        if (btn & 0x4000) {
            cur = *(s32 *)(g + 0x164);
            if (cur == 0) {
                *(s32 *)(g + 0x15C) |= 0x40;
                return func_00297FE0(0, 1, 64, 64, 1);
            }
            if (cur != 1) {
                return cur;
            }
            if (*(s32 *)(g + 0x268) == *(s32 *)(g + 0x270)) {
                func_0026EB78(g + 0x28, D_003879E0);
                *(s32 *)(D_003879D0 + 0x16C) = 3;
                return func_00297FE0(0, 1, 64, 64, 1);
            }
            return func_00297FE0(0, 7, 64, 64, 1);
        }
        if (btn & 0x1000) {
            func_0026EB78(g + 0x28, D_00376208);
            *(s32 *)(D_003879D0 + 0x16C) = 0;
            return func_00297FE0(0, 2, 64, 64, 1);
        }
        return 0;
    }

    if (state == 3) {
        btn = *(s32 *)(D_003B0B00 + 0x134);
        if (btn & 0x4000) {
            *(s32 *)(g + 0x15C) |= 1;
            *(s32 *)(D_003879D0 + 0x15C) |= 2;
            *(s32 *)(D_003879D0 + 0x170) = 15;
            return func_00297FE0(0, 1, 64, 64, 1);
        }
        if (btn & 0x1000) {
            func_0026EB78(g + 0x28, D_00376228);
            *(s32 *)(D_003879D0 + 0x16C) = 0;
            return func_00297FE0(0, 2, 64, 64, 1);
        }
        return btn & 0x1000;
    }
    return 3;
}
