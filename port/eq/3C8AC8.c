#include "common.h"

/* 0x003C8AC8: per-frame pad handler of a two-player customization menu ("fr_reel", "fr_type", "fr_color_select").
 * G = D_00423114 (menu object). Fields (all s32 unless noted):
 *   +0x188 current player, +0x18C flag word, +0x1C4 / +0x1C8 counts, +0x362C, +0x3628, +0x3640 (needed picks),
 *   +0x3644 (picks made). Per player p (index 4p added): +0x190 column, +0x198 row, +0x1A0 slot, +0x1A8 sub-cursor,
 *   +0x1B0 colour, +0x1B8 remembered colour, +0x1CC item table pointer (items are 44 bytes, id at +0, count at +4,
 *   variants from +8; item = table + 44 * (7 * row + column)).
 * Pad words: D_003B0B00 + 0x144 (edge buttons) and + 0x134. */

extern u8 *D_00423114 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

extern s32 rand();
extern s32 GetTimerSystemTime();

extern s32 func_0026EB60(u8 *obj);
extern void func_0026EB78(u8 *obj, const char *name);
extern u8 func_0024B6C8(u32 id);
extern s32 func_0024AD60(u8 *table, s32 *pos, s32 row);
extern s32 func_0024ACE8(u8 *table, s32 *pos, s32 row);
extern void func_0024AEA0(u8 *table, s32 *col, s32 *row, s32 n);
extern void func_0024ADE8(u8 *table, s32 *col, s32 *row, s32 n);
extern void func_00325370(s64 seed);
extern void func_003C6928(void);
extern void func_003C6968(s32 player);
extern void func_003C6408(s32 player);
extern void func_003C6670(void);
extern s32 func_003C6B98();
extern void func_003C8AA8(void);
extern s32 func_00297FE0(s32 a, s32 b, s32 c, s32 d, s32 e);

#define G D_00423114
#define GS(off) (*(s32 *)(G + (off)))
#define PLAYER GS(0x188)
#define FLAGS GS(0x18C)
#define PF(off) (*(s32 *)(G + PLAYER * 4 + (off)))
#define COL PF(0x190)
#define ROW PF(0x198)
#define SLOT PF(0x1A0)
#define SUBCUR PF(0x1A8)
#define COLOR PF(0x1B0)
#define TABLE (*(u8 **)(G + PLAYER * 4 + 0x1CC))
#define ITEM (TABLE + 44 * (7 * ROW + COL))
#define ITEM_ID (*(s32 *)ITEM)
#define ITEM_N (*(s32 *)(ITEM + 4))
#define NCOLORS func_0024B6C8(ITEM_ID)
/* remembered slot per (player, row, column) */
#define SAVED (*(s32 *)(G + 0x31F8 + 4 * (7 * ROW + 134 * PLAYER + COL)))
#define PICK(base) (*(s32 *)(G + GS(0x3644) * 4 + (base)))
#define PAD44 (*(u32 *)(D_003B0B00 + 0x144))
#define PAD34 (*(u32 *)(D_003B0B00 + 0x134))

s32 func_003C8AC8(s32 *done) {
    s32 idx, id, r;

    if (func_0026EB60(G + 0x48) == 0) {
        return 0;
    }

    /* 0x80: confirm slot / commit reel */
    if ((PAD44 & 0x80) && !(FLAGS & 0x100)) {
        if (FLAGS & 0x1000) {
            if (!(FLAGS & 0x40000000)) {
                return 0;
            }
            r = COLOR % 3;
            id = r - 1;
            if (id < 0) {
                id = 2;
            }
            COLOR = COLOR - r + id;
            if (!(COLOR < NCOLORS)) {
                COLOR = NCOLORS - 1;
            }
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        func_003C6928();
        SAVED = SLOT;
        func_0024AD60(TABLE, &COL, ROW);
        SLOT = SAVED;
        return func_00297FE0(0, 8, 0x40, 0x40, 1);
    }

    /* 0x20 */
    if ((PAD44 & 0x20) && !(FLAGS & 0x100)) {
        if (FLAGS & 0x1000) {
            if (!(FLAGS & 0x40000000)) {
                return 0;
            }
            COLOR = COLOR - COLOR % 3 + (COLOR % 3 + 1) % 3;
            if (!(COLOR < NCOLORS)) {
                COLOR = COLOR - COLOR % 3;
            }
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        func_003C6928();
        SAVED = SLOT;
        func_0024ACE8(TABLE, &COL, ROW);
        SLOT = SAVED;
        return func_00297FE0(0, 8, 0x40, 0x40, 1);
    }

    /* 0x10: up */
    if ((PAD44 & 0x10) && !(FLAGS & 0x100)) {
        if (FLAGS & 0x1000) {
            if (!(FLAGS & 0x40000000)) {
                SUBCUR--;
                if (SUBCUR < 0) {
                    SUBCUR = GS(0x1C4) - 1;
                }
                return func_00297FE0(0, 0, 0x40, 0x40, 1);
            }
            COLOR -= 3;
            if (COLOR < 0) {
                COLOR += 6;
                while (!(COLOR < NCOLORS)) {
                    COLOR -= 3;
                }
            }
            if (NCOLORS < 4) {
                return 1;
            }
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        if (GS(0x3628) < 2) {
            return 1;
        }
        func_003C6928();
        SAVED = SLOT;
        func_0024AEA0(TABLE, &COL, &ROW, GS(0x3628));
        SLOT = SAVED;
        func_003C6408(PLAYER);
        func_0026EB78(G + 0x70, "fr_reel_up");
        return func_00297FE0(1, 2, 0x40, 0x40, 1);
    }

    /* 0x40: down */
    if ((PAD44 & 0x40) && !(FLAGS & 0x100)) {
        if (FLAGS & 0x1000) {
            if (!(FLAGS & 0x40000000)) {
                SUBCUR++;
                if (GS(0x1C4) - 1 < SUBCUR) {
                    SUBCUR = 0;
                }
                return func_00297FE0(0, 0, 0x40, 0x40, 1);
            }
            COLOR += 3;
            if (!(COLOR < NCOLORS)) {
                COLOR = COLOR % 3;
            }
            if (NCOLORS < 4) {
                return 1;
            }
            return func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        if (GS(0x3628) < 2) {
            return 1;
        }
        func_003C6928();
        SAVED = SLOT;
        func_0024ADE8(TABLE, &COL, &ROW, GS(0x3628));
        SLOT = SAVED;
        func_003C6408(PLAYER);
        func_0026EB78(G + 0x70, "fr_reel_down");
        return func_00297FE0(1, 2, 0x40, 0x40, 1);
    }

    /* 0x400: previous slot */
    if ((PAD44 & 0x400) && !(FLAGS & 0x100)) {
        if (FLAGS & 0x1000) {
            return FLAGS & 0x1000;
        }
        if (ITEM_N == 0) {
            return (s32)ITEM;
        }
        func_003C6928();
        SLOT--;
        if (SLOT < 0) {
            SLOT = ITEM_N - 1;
        }
        func_003C6968(PLAYER);
        return func_00297FE0(0, 0, 0x40, 0x40, 1);
    }

    /* 0x800: next slot */
    if ((PAD44 & 0x800) && !(FLAGS & 0x100)) {
        if (FLAGS & 0x1000) {
            return FLAGS & 0x1000;
        }
        if (ITEM_N == 0) {
            return (s32)ITEM;
        }
        func_003C6928();
        SLOT++;
        if (ITEM_N - 1 < SLOT) {
            SLOT = 0;
        }
        func_003C6968(PLAYER);
        return func_00297FE0(0, 0, 0x40, 0x40, 1);
    }

    /* pad34 0x2000: switch player */
    if ((PAD34 & 0x2000) && (FLAGS & 0x20000100) == 0x20000000) {
        if (FLAGS & 0x1000) {
            return FLAGS & 0x1000;
        }
        func_003C6928();
        SAVED = SLOT;
        PLAYER ^= 1;
        func_003C6408(PLAYER);
        func_003C6968(PLAYER);
        SLOT = SAVED;
        return func_00297FE0(0, 1, 0x40, 0x40, 1);
    }

    /* pad34 0x4000: select */
    if ((PAD34 & 0x4000) && !(FLAGS & 0x100)) {
        if (!(FLAGS & 0x1000)) {
            /* enter the sub-state */
            s32 k;
            FLAGS |= 0x1000;
            k = COL + 7 * ROW;
            if (k >= 74) {
                FLAGS |= 0x200000 << GS(0x3644);
                FLAGS |= 0x40000000;
                PICK(0x3648) = ITEM_ID;
                PICK(0x3668) = 1;
                PICK(0x3688) = COLOR;
                PICK(0x36A8) = PLAYER;
                PICK(0x36C8) = COL + 7 * ROW;
                COLOR = PF(0x1B8);
                if (!(COLOR < NCOLORS)) {
                    COLOR = NCOLORS - 1;
                }
                func_0026EB78(G + 0x98, "fr_color_select_in");
                return func_00297FE0(0, 1, 0x40, 0x40, 1);
            }
            if (*(s32 *)(TABLE + 44 * k) == 0x82) {
                GS(0x1C4) = 2;
                if (SUBCUR == 2) {
                    SUBCUR = 0;
                }
            } else {
                GS(0x1C4) = 3;
            }
            func_0026EB78(G + 0x98, "fr_type_in");
            return func_00297FE0(1, 0, 0x40, 0x40, 1);
        }

        if (FLAGS & 0x40000000) {
            /* confirm colour pick */
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            PICK(0x3648) = ITEM_ID;
            PICK(0x3668) = SUBCUR;
            PICK(0x3688) = COLOR;
            PICK(0x36A8) = PLAYER;
            PICK(0x36C8) = COL + 7 * ROW;
            func_0026EB78(G + 0x98, "fr_color_select_out");
            PF(0x1B8) = COLOR;
            GS(0x3644) = GS(0x3644) + 1;
            func_003C6670();
            FLAGS &= ~0x1000;
            FLAGS &= ~0x40000000;
            if (GS(0x3644) != GS(0x3640)) {
                return GS(0x3640);
            }
            FLAGS |= 0x100;
            FLAGS |= 0x400;
            return func_003C6B98();
        }

        /* sub-cursor dispatch */
        if (SUBCUR == 1) {
            FLAGS |= 0x40000;
        } else if (SUBCUR == 2) {
            if (ITEM_ID == 0x82) {
                return func_00297FE0(0, 7, 0x40, 0x40, 1);
            }
            if (FLAGS & 0xC000) {
                return FLAGS & 0xC000;
            }
            FLAGS |= 0x4000;
            return func_00297FE0(0, 1, 0x40, 0x40, 1);
        } else if (SUBCUR != 0) {
            return (SUBCUR < 2) ? 1 : 2;
        }

        func_00297FE0(0, 1, 0x40, 0x40, 1);
        if (ITEM_ID != 0x82) {
            func_0026EB78(G + 0x98, "fr_color_select");
            FLAGS |= 0x40000000;
            COLOR = PF(0x1B8);
            r = NCOLORS;
            if (COLOR < r) {
                return r;
            }
            r = NCOLORS - 1;
            COLOR = r;
            return r;
        }

        /* random item for the 0x82 slot */
        func_0026EB78(G + 0x98, "fr_type_out");
        func_00325370(GetTimerSystemTime());
        do {
            idx = rand() % GS(0x1C8);
            id = *(s32 *)(TABLE + 44 * idx);
        } while (id >= 0x82 || id == 0x62);
        if (*(s32 *)(TABLE + 44 * idx + 4) != 0) {
            r = rand() % *(s32 *)(TABLE + 44 * idx + 4);
            id = *(s32 *)(TABLE + 44 * idx + 4 * r + 8);
        }
        r = rand();
        COLOR = r % func_0024B6C8(id);
        PICK(0x3648) = id;
        PICK(0x3668) = SUBCUR;
        PICK(0x3688) = COLOR;
        PICK(0x36A8) = PLAYER;
        PICK(0x36C8) = idx;
        GS(0x3644) = GS(0x3644) + 1;
        func_003C6670();
        FLAGS &= ~0x1000;
        FLAGS &= ~0x40000000;
        if (GS(0x3644) != GS(0x3640)) {
            return GS(0x3640);
        }
        FLAGS |= 0x100;
        FLAGS |= 0x400;
        return func_003C6B98();
    }

    /* pad34 0x1000: back */
    r = PAD34 & 0x1000;
    if (r == 0) {
        return r;
    }
    if (FLAGS & 0x1000) {
        if (FLAGS & 0x40000000) {
            func_0026EB78(G + 0x98, "fr_color_select_out");
        } else {
            func_0026EB78(G + 0x98, "fr_type_out");
        }
        FLAGS &= ~0x1000;
        FLAGS &= ~0x40000000;
        return func_00297FE0(0, 2, 0x40, 0x40, 1);
    }
    if (GS(0x3644) == 0) {
        if (GS(0x362C) == 4) {
            func_003C8AA8();
            *done = 0;
            return func_00297FE0(0, 2, 0x40, 0x40, 1);
        }
        return 4;
    }
    {
        u32 bit = 0x200000 << GS(0x3644);
        if (FLAGS & bit) {
            FLAGS ^= bit;
        }
    }
    GS(0x3644) = GS(0x3644) - 1;
    func_003C6670();
    if (FLAGS & 0x100) {
        FLAGS ^= 0x100;
    }
    if (FLAGS & 0x400) {
        FLAGS ^= 0x400;
    }
    return func_00297FE0(0, 2, 0x40, 0x40, 1);
}
