#include "common.h"

extern u8 *D_004279D0 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_00428BE0[] __attribute__((section(".data")));
extern u8 D_00428BF0[] __attribute__((section(".data")));
extern u8 D_00428C00[] __attribute__((section(".data")));
extern u8 D_00428C18[] __attribute__((section(".data")));
extern u8 D_00428C28[] __attribute__((section(".data")));
extern u8 D_00428C38[] __attribute__((section(".data")));

s32 func_26EB60(u8 *p);
void func_26EB78(u8 *p, u8 *q);
s32 func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_00243A80(s32 a0, s32 a1, s32 a2);
s32 func_003E6848(void);
extern s32 func_29C7E0();
extern s32 func_29C550();
extern s32 func_29C820();

#define G (D_004279D0)
#define W(off) (*(s32 *)(G + (off)))
#define BTN_A (*(s32 *)(D_003B0B00 + 0x144))
#define BTN_B (*(s32 *)(D_003B0B00 + 0x134))

/* G->0x188..0x197 (16 bytes) -> D_00387F2C + 0x1094 */
static void save_pos(void) {
    __builtin_memcpy(D_00387F2C + 0x1094, G + 0x188, 16);
}
static void load_pos(void) {
    __builtin_memcpy(G + 0x188, D_00387F2C + 0x1094, 16);
}
static void mark_dirty(void) {
    *(s32 *)(D_3876A4 + 0x18) |= 1;
}

/* 0x003E7738(out): per-frame input step of the frame/layout/vibration options screen, G = D_004279D0.
   F0 = G->0xF0 flags: 1 done, 2 type sub-menu, 4 vibration sub-menu, 8 layout sub-menu, 0x10 changed, 0x20 closing.
   BTN_A = D_003B0B00+0x144 (repeat/direction bits 0x10 up, 0x20 right, 0x40 down, 0x80 left),
   BTN_B = D_003B0B00+0x134 (0x4000 confirm, 0x1000 cancel, 0x8 start). */
s32 func_003E7738(s32 *arg0) {
    s32 r;

    if (func_26EB60(G + 0x10) == 0) {
        return 0;
    }

    if (W(0xF0) & 0x20) {
        if (W(0x31C) != 0) {
            return W(0x31C);
        }
        if (W(0x324) <= 0) {
            r = W(0xF0) ^ 0x20;
            W(0xF0) = r;
            return r;
        }
        if (W(0xF0) & 8) {
            W(0x190) = 0;
            W(0x194) = 0;
            mark_dirty();
            save_pos();
        } else {
            W(0x188) = 0;
            W(0x18C) = 0;
            W(0x190) = 0;
            W(0x194) = 0;
            mark_dirty();
            save_pos();
        }
        r = W(0xF0) ^ 0x20;
        W(0xF0) = r;
        return r;
    }

    if (W(0xF0) & 8) {
        if (BTN_A & 0x10) {
            W(0x194) = W(0x194) - 1;
            if (W(0x194) < -0x10) {
                W(0x194) = -0x10;
            } else {
                func_00297FE0(0, 0, 0x40, 0x40, 1);
            }
        } else if (BTN_A & 0x40) {
            W(0x194) = W(0x194) + 1;
            if (W(0x194) < 0x11) {
                func_00297FE0(0, 0, 0x40, 0x40, 1);
            } else {
                W(0x194) = 0x10;
            }
        } else if (BTN_A & 0x80) {
            W(0x190) = W(0x190) - 1;
            if (W(0x190) < -0x10) {
                W(0x190) = -0x10;
            } else {
                func_00297FE0(0, 0, 0x40, 0x40, 1);
            }
        } else if (BTN_A & 0x20) {
            W(0x190) = W(0x190) + 1;
            if (W(0x190) < 0x11) {
                func_00297FE0(0, 0, 0x40, 0x40, 1);
            } else {
                W(0x190) = 0x10;
            }
        } else if (BTN_B & 0x8) {
            W(0xF0) = W(0xF0) | 0x20;
            W(0x31C) = 1;
            func_29C7E0(0);
            func_29C550(0);
            func_29C820(1);
            W(0x324) = 0;
            return (s32)G;
        } else {
            if (!(BTN_B & 0x1000)) {
                return -9;
            }
            W(0xF0) = W(0xF0) & ~8;
            func_26EB78(G + 0x10, D_00428BE0);
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            __builtin_memcpy(G + 0x188, D_00387F2C + 0x1094, 16);
            return *(s32 *)(D_00387F2C + 0x1094);
        }
        mark_dirty();
        save_pos();
        return (s32)G;
    }

    if (W(0xF0) & 2) {
        if (BTN_A & 0x20) {
            if (!(W(0xF0) & 0x10)) {
                W(0x304) = W(0xF8);
            }
            W(0xF0) = W(0xF0) | 0x10;
            W(0xF8) = W(0xF8) + 1;
            if (W(0xF8) >= 3) {
                W(0xF8) = 0;
            }
        } else if (BTN_A & 0x80) {
            if (!(W(0xF0) & 0x10)) {
                W(0x304) = W(0xF8);
            }
            W(0xF0) = W(0xF0) | 0x10;
            W(0xF8) = W(0xF8) - 1;
            if (W(0xF8) < 0) {
                W(0xF8) = 2;
            }
        } else if (BTN_B & 0x4000) {
            W(0x188) = W(0xF8);
            mark_dirty();
            W(0xF0) = W(0xF0) & ~2;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            func_26EB78(G + 0x10, D_00428BF0);
            func_003E6848();
            save_pos();
            return (s32)D_00387F2C;
        } else if (BTN_B & 0x1000) {
            load_pos();
            W(0xF0) = W(0xF0) & ~2;
            func_26EB78(G + 0x10, D_00428BF0);
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            return func_003E6848();
        } else {
            return 0x380000;
        }
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        return func_003E6848();
    }

    if (W(0xF0) & 4) {
        if (BTN_A & 0x20) {
            W(0xF8) = W(0xF8) + 1;
            if (W(0xF8) >= 2) {
                W(0xF8) = 0;
            }
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        } else if (BTN_A & 0x80) {
            W(0xF8) = W(0xF8) - 1;
            if (W(0xF8) < 0) {
                W(0xF8) = 1;
            }
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        } else if (BTN_B & 0x4000) {
            W(0x18C) = W(0xF8);
            mark_dirty();
            W(0xF0) = W(0xF0) & ~4;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            func_26EB78(G + 0x10, D_00428C00);
            func_003E6848();
            save_pos();
            return (s32)D_00387F2C;
        } else if (BTN_B & 0x1000) {
            load_pos();
            W(0xF0) = W(0xF0) & ~4;
            func_26EB78(G + 0x10, D_00428C00);
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            return func_003E6848();
        }
        return 0x380000;
    }

    /* top-level list */
    if (BTN_A & 0x10) {
        W(0xF4) = W(0xF4) - 1;
        if (W(0xF4) < 0) {
            W(0xF4) = 3;
        }
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        return func_003E6848();
    }
    if (BTN_A & 0x40) {
        W(0xF4) = W(0xF4) + 1;
        if (W(0xF4) >= 4) {
            W(0xF4) = 0;
        }
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        return func_003E6848();
    }
    if (BTN_B & 0x4000) {
        s32 a1 = 1;
        s32 sel = W(0xF4);
        if (sel == 0) {
            W(0xF0) = W(0xF0) | 2;
            W(0xF8) = W(0x188);
            func_26EB78(G + 0x10, D_00428C18);
            func_003E6848();
        } else if (sel == 1) {
            W(0xF0) = W(0xF0) | 4;
            W(0xF8) = W(0x18C);
            func_26EB78(G + 0x10, D_00428C28);
        } else if (sel == 2) {
            W(0xF0) = W(0xF0) | 8;
            func_26EB78(G + 0x10, D_00428C38);
        } else if (sel == 3) {
            W(0xF0) = W(0xF0) | 0x20;
            W(0x31C) = a1;
            func_29C7E0(0);
            func_29C550(0);
            func_29C820(1);
            W(0x324) = 0;
        }
        return func_00297FE0(0, 1, 0x40, 0x40, 1);
    }
    if (BTN_B & 0x1000) {
        /* copy 0xAC bytes G+0xFC -> D_00387F2C+0x1008 */
        __builtin_memcpy(D_00387F2C + 0x1008, G + 0xFC, 0xAC);
        W(0xF0) = W(0xF0) | 1;
        *arg0 = 0;
        func_00243A80(0, 0, 0);
        return func_00297FE0(0, 2, 0x40, 0x40, 1);
    }
    return 0x380000;
}
