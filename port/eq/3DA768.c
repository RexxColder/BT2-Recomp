#include "common.h"

/* menu overlay: fusion/item list menu, per-frame input handler (4 columns of items) */

s32 func_0026EB60(u8 *obj);
void func_0026EB78(u8 *obj, const char *name);
void func_0026EAE0(u8 *obj, s32 v);
void func_0026EA88(u8 *obj);
void func_00297FE0(s32 a, s32 sound, s32 c, s32 d, s32 e);
void func_00251088(void);
void func_00251030(s32 v);
s32 func_001018B8(void);
void func_002493C0(s32 a, s32 b, s32 c, s32 d, s32 e);
void func_003D8798(void);
void func_003DA738(void);
s32 func_003D88A8(s32 a, s32 b);
void func_00298460(s32 id, s32 v, s32 one);

extern u8 *D_004263E8 __attribute__((section(".data")));   /* menu state */
extern u8 *D_00387F2C;                                      /* save data */
extern u32 D_003B0C34;                                      /* buttons pressed */
extern u32 D_003B0C44;                                      /* buttons repeat */
extern char D_00426E50[], D_00426E68[], D_00426E78[], D_00426E80[], D_00426E98[];

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))

#define M_FLAGS(m)     U32(m, 0x154)
#define M_COL(m)       S32(m, 0x158)
#define M_CURSOR(m)    S32(m, 0x15C + 4 * M_COL(m))   /* selected row of column */
#define M_TOP(m)       S32(m, 0x16C + 4 * M_COL(m))   /* first visible row */
#define M_LEN(m)       S32(m, 0x6E0C + 4 * M_COL(m))  /* rows in column */
#define M_ITEM_ID(m)   S32(m, 0x17C + 0x1B24 * M_COL(m) + 12 * M_CURSOR(m))
#define M_ITEM_CNT(m)  S32(m, 0x184 + 0x1B24 * M_COL(m) + 12 * M_CURSOR(m))
#define M_SEL_A(m)     S32(m, 0x6E24)
#define M_SEL_B(m)     S32(m, 0x6E28)
#define M_RESULT(m)    S32(m, 0x6E2C)
#define M_CHOICE(m)    S32(m, 0x6E30)
#define M_STATE(m)     S32(m, 0x6E38)
#define M_ENTRY_CNT(m, id) S32(*(u8 **)((m) + 0x14), 48 * (id) + 0x10)
#define SAVE_FLAGS(id) U16(D_00387F2C, 0x1F30 + 4 * (id))
#define SAVE_COUNT(id) S16(D_00387F2C, 0x1F32 + 4 * (id))

#define BTN_CONFIRM 0x4000
#define BTN_CANCEL  0x1000
#define BTN_INFO    0x8000

#define Beep(snd) func_00297FE0(0, (snd), 0x40, 0x40, 1)

/* common tail of the "item chosen" paths: clear bit 1 of the chosen item's save flags */
#define ClearNewFlag(m) do { if (SAVE_FLAGS(M_ITEM_ID(m)) & 2) SAVE_FLAGS(M_ITEM_ID(m)) &= ~2; } while (0)

void func_003DA768(u32 *exitFlag) {
    u8 *m = D_004263E8;
    u32 flags;
    s32 id;
    s32 col;
    s32 cur;
    s32 top;
    s32 len;
    s32 offs;

    if (func_0026EB60(m + 0x1C) == 0) {
        return;
    }
    flags = M_FLAGS(m);

    /* bit 0x20: item info popup open */
    if (flags & 0x20) {
        if (D_003B0C34 & (BTN_INFO | BTN_CANCEL)) {
            func_00251088();
            M_FLAGS(m) &= ~0x20;
            Beep(2);
        }
        return;
    }

    /* bit 0x40: fusion info window animating out/in */
    if (flags & 0x40) {
        M_FLAGS(m) = flags & ~0x80;
        if (!(D_003B0C34 & BTN_CONFIRM) && func_001018B8() != 5) {
            return;
        }
        if (M_STATE(m) == 0x17) {
            M_STATE(m) = 0x18;
            func_002493C0(S32(m, 0xC), 0x36B2, 0x3ACB, 0, M_STATE(m));
        } else {
            M_SEL_B(m) = -1;
            func_003D8798();
            M_FLAGS(m) &= ~0x40;
            func_0026EB78(m + 0x1C, D_00426E50);
        }
        if (D_003B0C34 & BTN_CONFIRM) {
            Beep(1);
        }
        return;
    }

    if (!(flags & 0x4)) {
        /* ---- browsing the item list ---- */
        u32 rep = D_003B0C44;

        if (rep & 0x50) {
            /* up / down */
            if (rep & 0x10) {
                M_CURSOR(m) = M_CURSOR(m) - 1;
                if (M_CURSOR(m) >= 0) {
                    Beep(0);
                } else {
                    M_CURSOR(m) = 0;
                }
            } else if (rep & 0x40) {
                M_CURSOR(m) = M_CURSOR(m) + 1;
                if (M_CURSOR(m) < M_LEN(m)) {
                    Beep(0);
                } else {
                    M_CURSOR(m) = M_LEN(m) - 1;
                }
                if (M_CURSOR(m) < 0) {
                    M_CURSOR(m) = 0;
                }
            }
            cur = M_CURSOR(m);
            top = M_TOP(m);
            if (cur < top + 4) {
                if (cur < top) {
                    M_TOP(m) = cur;
                }
            } else {
                M_TOP(m) = cur - 3;
            }
            return;
        }

        if (rep & 0xC00) {
            /* page down (0x800) / page up (0x400) */
            cur = M_CURSOR(m);
            top = M_TOP(m);
            offs = cur - top;
            if (rep & 0x800) {
                len = M_LEN(m);
                if (top < len - 4) {
                    M_TOP(m) = top + 4;
                    if (M_LEN(m) - 4 < M_TOP(m)) {
                        M_TOP(m) = M_LEN(m) - 4;
                    }
                } else {
                    if (top == len - 4) {
                        if (cur != len - 1) {
                            Beep(0);
                        }
                        M_CURSOR(m) = M_TOP(m) + 3;
                    }
                    return;
                }
            } else {
                if (!(rep & 0x400)) {
                    return;
                }
                if (top <= 0) {
                    if (top == 0) {
                        if (cur != 0) {
                            Beep(0);
                        }
                        M_CURSOR(m) = M_TOP(m);
                    }
                    return;
                }
                M_TOP(m) = top - 4;
                if (M_TOP(m) < 0) {
                    M_TOP(m) = 0;
                }
            }
            Beep(0);
            M_CURSOR(m) = M_TOP(m) + offs;
            return;
        }

        if (rep & 0x200) {
            /* jump to last row */
            len = M_LEN(m) - 1;
            if (M_CURSOR(m) < len) {
                M_CURSOR(m) = len;
                M_TOP(m) = M_LEN(m) - 4;
                Beep(0);
            }
            return;
        }

        if (rep & 0x100) {
            /* jump to first row */
            if (M_CURSOR(m) > 0) {
                M_CURSOR(m) = 0;
                M_TOP(m) = 0;
                Beep(0);
            }
            return;
        }

        if (rep & 0xA0) {
            /* left / right: change column */
            if (rep & 0x80) {
                M_COL(m) = M_COL(m) - 1;
                if (M_COL(m) < 0) {
                    M_COL(m) = 3;
                }
            } else if (rep & 0x20) {
                M_COL(m) = M_COL(m) + 1;
                if (M_COL(m) >= 4) {
                    M_COL(m) = 0;
                }
            }
            Beep(0);
            return;
        }

        if (D_003B0C34 & BTN_INFO) {
            id = M_ITEM_ID(m);
            if (id != -1 && (SAVE_FLAGS(id) & 1)) {
                if (SAVE_FLAGS(id) & 2) {
                    SAVE_FLAGS(id) &= ~2;
                }
                func_00251030(60);
                M_FLAGS(m) |= 0x20;
                Beep(1);
            }
            return;
        }

        if (D_003B0C34 & BTN_CONFIRM) {
            id = M_ITEM_ID(m);
            if (id == -1) {
                return;
            }
            if (M_ITEM_CNT(m) <= 0) {
                Beep(7);
                return;
            }
            if (M_SEL_A(m) == -1) {
                /* first item picked */
                M_SEL_A(m) = id;
                func_003D8798();
                Beep(1);
            } else if (func_003D88A8(M_SEL_A(m), id) < 0) {
                /* the pair cannot fuse */
                M_SEL_B(m) = M_ITEM_ID(m);
                M_STATE(m) = 0x17;
                func_003DA738();
                Beep(2);
                func_0026EB78(m + 0x1C, D_00426E68);
                M_FLAGS(m) |= 0x40;
            } else if (S16(D_00387F2C, 0x2356) > 0) {
                /* fusion possible and a fusion left: ask to confirm */
                M_SEL_B(m) = M_ITEM_ID(m);
                M_FLAGS(m) |= 0x4;
                M_STATE(m) = 0x11;
                func_003DA738();
                func_0026EB78(m + 0x1C, D_00426E68);
                func_0026EAE0(m + 0x44, 60);
                func_0026EA88(m + 0x44);
                M_CHOICE(m) = 1;
                Beep(1);
                M_FLAGS(m) |= 0x80;
            } else {
                /* no fusions left */
                M_SEL_B(m) = M_ITEM_ID(m);
                M_STATE(m) = 0x19;
                func_003DA738();
                Beep(2);
                func_0026EB78(m + 0x1C, D_00426E68);
                M_FLAGS(m) |= 0x40;
            }
            ClearNewFlag(m);
            return;
        }

        if (D_003B0C34 & BTN_CANCEL) {
            if (M_SEL_A(m) == -1) {
                *exitFlag = 0;
                M_FLAGS(m) = 2;
            } else {
                M_SEL_A(m) = -1;
                func_003D8798();
            }
            Beep(2);
        }
        return;
    }

    if (!(flags & 0x8)) {
        /* ---- confirm dialog (yes/no) ---- */
        u32 rep = D_003B0C44;

        if (rep & 0x10) {
            M_CHOICE(m) = M_CHOICE(m) - 1;
            if (M_CHOICE(m) < 0) {
                M_CHOICE(m) = 1;
            }
            Beep(0);
            return;
        }
        if (rep & 0x40) {
            M_CHOICE(m) = M_CHOICE(m) + 1;
            if (M_CHOICE(m) >= 2) {
                M_CHOICE(m) = 0;
            }
            Beep(0);
            return;
        }
        if ((D_003B0C34 & BTN_CONFIRM) && M_CHOICE(m) == 0) {
            /* yes: start the fusion */
            M_STATE(m) = 0x12;
            func_002493C0(S32(m, 0xC), 0x36B2, 0x3ACB, 0, M_STATE(m));
            func_0026EB78(m + 0x44, D_00426E78);
            M_RESULT(m) = func_003D88A8(M_SEL_A(m), M_SEL_B(m));
            S16(D_00387F2C, 0x2356) = S16(D_00387F2C, 0x2356) - 1;
            M_FLAGS(m) |= 0x8;
            M_FLAGS(m) &= ~0x80;
            Beep(1);
            return;
        }
        if (!(D_003B0C34 & BTN_CANCEL)) {
            if (!(D_003B0C34 & BTN_CONFIRM)) {
                return;
            }
            if (M_CHOICE(m) != 1) {
                return;
            }
        }
        /* no / cancel */
        M_FLAGS(m) &= ~0x4;
        M_STATE(m) = 0x16;
        M_FLAGS(m) |= 0x40;
        func_003DA738();
        func_0026EB78(m + 0x44, D_00426E78);
        Beep(2);
        return;
    }

    /* ---- fusion animation running (flag 0x8) ---- */
    if (flags & 0x10) {
        /* finished: back to the list */
        M_FLAGS(m) = flags & ~0x1C;
        M_RESULT(m) = -1;
        M_SEL_A(m) = -1;
        M_SEL_B(m) = -1;
        func_003D8798();
        func_0026EB78(m + 0x1C, D_00426E98);
        return;
    }

    if (M_STATE(m) == 0x12) {
        if (func_001018B8() != 5 && !(D_003B0C34 & BTN_CONFIRM)) {
            return;
        }
        func_0026EB78(m + 0x1C, D_00426E80);
        if (D_003B0C34 & BTN_CONFIRM) {
            Beep(1);
        }
        return;
    }

    if (!(D_003B0C34 & BTN_CONFIRM)) {
        return;
    }
    M_FLAGS(m) = flags | 0x10;
    if (M_RESULT(m) != -1) {
        func_00298460(M_RESULT(m), S32(*(u8 **)(m + 0x14), 48 * M_RESULT(m) + 0x10), 1);
    }
    if (M_ENTRY_CNT(m, M_SEL_A(m)) >= 2) {
        SAVE_COUNT(M_SEL_A(m)) = SAVE_COUNT(M_SEL_A(m)) - 1;
    }
    if (SAVE_COUNT(M_SEL_A(m)) < 0) {
        SAVE_COUNT(M_SEL_A(m)) = 0;
    }
    if (M_ENTRY_CNT(m, M_SEL_B(m)) >= 2) {
        SAVE_COUNT(M_SEL_B(m)) = SAVE_COUNT(M_SEL_B(m)) - 1;
    }
    if (SAVE_COUNT(M_SEL_B(m)) < 0) {
        SAVE_COUNT(M_SEL_B(m)) = 0;
    }
    Beep(1);
}
