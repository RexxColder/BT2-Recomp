#include "common.h"

/* 0x00407BE0: per-player input handler of the selection screen (reel / colour select / type select).
 * M = *D_0042BB74 (menu block), per-player fields at M + off + 4 * pl (pl = loop index + M->36D0):
 *   0x214 column, 0x21C row, 0x224 cursor, 0x22C sub-state, 0x234 colour index, 0x23C saved colour, 0x244 colour list id,
 *   0x24C sub-state count, 0x254 last picked cell, 0x260 table of 44-byte entries (+0 id, +4 count).
 * M+0x210 state flags: 0x100 locked, 0x400 idle, 0x1000 type select, 0x4000 pick, 0x40000 and 0x100000 colour select
 * (each shifted by pl). M+0x328C + 4 * (7 * row + 134 * pl + col) remembers the cursor per cell. Pad words are
 * D_003B0B00 + 0x134 + 0x180 * i: +0 held bits, +0x10 pressed bits.
 * Every handler ends the iteration; ta/tb request the final func_297FE0(ta, tb, 64, 64, 1) (sound/effect).
 * Returns 0 normally, 0 when func_26EB60 fails, 1 or 2 (stale v0) when the mode gives no player. */
extern u8 *D_0042BB74 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

extern char D_0042DEC0[]; /* fr_reel_up */
extern char D_0042DED0[]; /* fr_reel_down */
extern char D_0042DEE0[]; /* fr_color_select_out */
extern char D_0042DEF8[]; /* fr_out */
extern char D_0042DF00[]; /* fr_type_out */
extern char D_0042DF10[]; /* fr_color_select */
extern char D_0042DF20[]; /* fr_color_select_in */
extern char D_0042DF38[]; /* fr_type_in */

extern s32 func_26EB60();
extern s32 func_26EB78();
extern s32 func_26EA88();
extern s32 func_24B6C8();
extern s32 func_24AD60();
extern s32 func_24ACE8();
extern s32 func_24AEA0();
extern s32 func_24ADE8();
extern void func_00405B40(s32 pl);
extern void func_00405BA0(s32 pl);
extern void func_00405500(s32 pl);
extern void func_00407BC0(void);
extern void func_00297FE0(s32 a, s32 b, s32 w, s32 h, s32 flag);

#define M D_0042BB74
#define PL (i + *(s32 *)(M + 0x36D0))
#define FIELD(off) (*(s32 *)(M + (off) + 4 * PL))
#define COL FIELD(0x214)
#define ROW FIELD(0x21C)
#define CUR FIELD(0x224)
#define SUB FIELD(0x22C)
#define SEL FIELD(0x234)
#define SELSAVE FIELD(0x23C)
#define COLORS FIELD(0x244)
#define SUBCOUNT FIELD(0x24C)
#define TBL (*(u8 **)(M + 0x260 + 4 * PL))
#define ENTRY (TBL + 44 * (7 * ROW + COL))
#define SAVED (*(s32 *)(M + 0x328C + 4 * (7 * ROW + 134 * PL + COL)))
#define FLAGS (*(u32 *)(M + 0x210))
#define BIT(b) ((u32)(b) << PL)
#define CLEAR_IF_SET(b) \
    do { \
        if (FLAGS & (b)) { \
            FLAGS ^= (b); \
        } \
    } while (0)
#define TAIL(a, b) \
    do { \
        ta = (a); \
        tb = (b); \
        doTail = 1; \
    } while (0)

s32 func_00407BE0(s32 *out) {
    s32 n = 0;
    s32 mode;
    s32 i;
    s32 ta = 0;
    s32 tb = 0;
    s32 doTail;
    s32 r;
    s32 nv;
    s32 idx;
    u32 *pad;
    s32 res;

    res = func_26EB60(M + 0x50);
    if (!res) {
        return res;
    }
    mode = *(s32 *)(M + 0x36C4);
    if (mode == 1) {
        n = 2;
    } else if (mode == 0 || mode == 2) {
        n = 1;
    }
    if (n == 0) {
        return (mode >= 3) ? 2 : 1;
    }

    for (i = 0; i < n; i++) {
        pad = (u32 *)(D_003B0B00 + 0x134 + 0x180 * i);
        doTail = 0;
        do {
            /* pressed 0x80: move the cursor/colour one step back */
            if ((pad[4] & 0x80) && !(FLAGS & BIT(0x100))) {
                if (!(FLAGS & BIT(0x1000))) {
                    func_00405B40(PL);
                    SAVED = CUR;
                    func_24AD60(TBL, M + 0x214 + 4 * PL, ROW);
                    CUR = SAVED;
                    TAIL(0, 8);
                    break;
                }
                if (!(FLAGS & BIT(0x100000))) {
                    break;
                }
                r = SEL % 3;
                SEL = SEL - r + ((r - 1 < 0) ? 2 : r - 1);
                if (!(SEL < func_24B6C8(COLORS))) {
                    SEL = func_24B6C8(COLORS) - 1;
                }
                TAIL(0, 0);
                break;
            }
            /* pressed 0x20: step forward */
            if ((pad[4] & 0x20) && !(FLAGS & BIT(0x100))) {
                if (!(FLAGS & BIT(0x1000))) {
                    func_00405B40(PL);
                    SAVED = CUR;
                    func_24ACE8(TBL, M + 0x214 + 4 * PL, ROW);
                    CUR = SAVED;
                    TAIL(0, 8);
                    break;
                }
                if (!(FLAGS & BIT(0x100000))) {
                    break;
                }
                r = SEL % 3;
                SEL = SEL - r + (r + 1) % 3;
                if (!(SEL < func_24B6C8(COLORS))) {
                    SEL -= SEL % 3;
                }
                TAIL(0, 0);
                break;
            }
            /* pressed 0x10: up */
            if ((pad[4] & 0x10) && !(FLAGS & BIT(0x100))) {
                if (FLAGS & BIT(0x1000)) {
                    if (FLAGS & BIT(0x100000)) {
                        SEL -= 3;
                        if (SEL < 0) {
                            nv = SEL + 6;
                            for (;;) {
                                SEL = nv;
                                if (SEL < func_24B6C8(COLORS)) {
                                    break;
                                }
                                nv = SEL - 3;
                            }
                        }
                        if (func_24B6C8(COLORS) < 4) {
                            break;
                        }
                        TAIL(0, 0);
                        break;
                    }
                    SUB -= 1;
                    if (SUB < 0) {
                        SUB = SUBCOUNT - 1;
                    }
                    TAIL(0, 0);
                    break;
                }
                if (*(s32 *)(M + 0x36BC) < 2) {
                    break;
                }
                func_00405B40(PL);
                SAVED = CUR;
                func_24AEA0(TBL, M + 0x214 + 4 * PL, M + 0x21C + 4 * PL, *(s32 *)(M + 0x36BC));
                CUR = SAVED;
                func_00405500(PL);
                func_26EB78(M + 40 * PL + 0x78, D_0042DEC0);
                TAIL(1, 2);
                break;
            }
            /* pressed 0x40: down */
            if ((pad[4] & 0x40) && !(FLAGS & BIT(0x100))) {
                if (FLAGS & BIT(0x1000)) {
                    if (FLAGS & BIT(0x100000)) {
                        SEL += 3;
                        if (!(SEL < func_24B6C8(COLORS))) {
                            SEL = SEL % 3;
                        }
                        if (func_24B6C8(COLORS) < 4) {
                            break;
                        }
                        TAIL(0, 0);
                        break;
                    }
                    SUB += 1;
                    if (SUBCOUNT - 1 < SUB) {
                        SUB = 0;
                    }
                    TAIL(0, 0);
                    break;
                }
                if (*(s32 *)(M + 0x36BC) < 2) {
                    break;
                }
                func_00405B40(PL);
                SAVED = CUR;
                func_24ADE8(TBL, M + 0x214 + 4 * PL, M + 0x21C + 4 * PL, *(s32 *)(M + 0x36BC));
                CUR = SAVED;
                func_00405500(PL);
                func_26EB78(M + 40 * PL + 0x78, D_0042DED0);
                TAIL(1, 2);
                break;
            }
            /* pressed 0x400: previous entry of the cell table */
            if ((pad[4] & 0x400) && !(FLAGS & BIT(0x100))) {
                if (FLAGS & BIT(0x1000)) {
                    break;
                }
                if (*(s32 *)(ENTRY + 4) == 0) {
                    break;
                }
                func_00405B40(PL);
                CUR -= 1;
                if (CUR < 0) {
                    CUR = *(s32 *)(ENTRY + 4) - 1;
                }
                SAVED = CUR;
                func_00405BA0(PL);
                TAIL(0, 0);
                break;
            }
            /* pressed 0x800: next entry of the cell table */
            if ((pad[4] & 0x800) && !(FLAGS & BIT(0x100))) {
                if (FLAGS & BIT(0x1000)) {
                    break;
                }
                if (*(s32 *)(ENTRY + 4) == 0) {
                    break;
                }
                func_00405B40(PL);
                CUR += 1;
                if (*(s32 *)(ENTRY + 4) - 1 < CUR) {
                    CUR = 0;
                }
                SAVED = CUR;
                func_00405BA0(PL);
                TAIL(0, 0);
                break;
            }
            /* held 0x4000: confirm */
            if ((pad[0] & 0x4000) && !(FLAGS & BIT(0x100))) {
                if (!(FLAGS & BIT(0x1000))) {
                    FLAGS |= BIT(0x1000);
                    FIELD(0x254) = COL + 7 * ROW;
                    idx = COL + 7 * ROW;
                    if (idx >= 0x4A) {
                        FLAGS |= BIT(0x40000);
                        FLAGS |= BIT(0x1000);
                        FLAGS |= BIT(0x100000);
                        func_26EB78(M + 40 * PL + 0xC8, D_0042DF20);
                        SEL = SELSAVE;
                        if (!(SEL < func_24B6C8(COLORS))) {
                            SEL = func_24B6C8(COLORS) - 1;
                        }
                        TAIL(0, 1);
                        break;
                    }
                    if (*(s32 *)(TBL + 44 * idx) == 0x82) {
                        SUBCOUNT = 2;
                        if (SUB == 2) {
                            SUB = 0;
                        }
                    } else {
                        SUBCOUNT = 3;
                    }
                    func_26EB78(M + 40 * PL + 0xC8, D_0042DF38);
                    TAIL(1, 0);
                    break;
                }
                if (FLAGS & BIT(0x100000)) {
                    func_00297FE0(0, 1, 64, 64, 1);
                    FLAGS |= BIT(0x100);
                    FLAGS |= BIT(0x400);
                    FLAGS ^= BIT(0x1000);
                    FLAGS ^= BIT(0x100000);
                    *(s32 *)(M + 0x36D4) = 15;
                    func_26EB78(M + 40 * PL + 0xC8, D_0042DEE0);
                    func_26EB78(M + 40 * PL + 0x78, D_0042DEF8);
                    SELSAVE = SEL;
                    if (*(s32 *)(M + 0x36C4) != 1) {
                        *(s32 *)(M + 0x36D0) = 1;
                    }
                    break;
                }
                switch (SUB) {
                case 1:
                    FLAGS |= BIT(0x40000);
                    /* fall through */
                case 0:
                    func_00297FE0(0, 1, 64, 64, 1);
                    if (*(s32 *)ENTRY == 0x82) {
                        FLAGS |= BIT(0x100);
                        FLAGS |= BIT(0x400);
                        CLEAR_IF_SET(BIT(0x1000));
                        CLEAR_IF_SET(BIT(0x100000));
                        *(s32 *)(M + 0x36D4) = 15;
                        func_26EB78(M + 40 * PL + 0xC8, D_0042DF00);
                        func_26EB78(M + 40 * PL + 0x78, D_0042DEF8);
                        if (*(s32 *)(M + 0x36C4) != 1) {
                            *(s32 *)(M + 0x36D0) = 1;
                        }
                    } else {
                        FLAGS |= BIT(0x100000);
                        func_26EB78(M + 40 * PL + 0xC8, D_0042DF10);
                        SEL = SELSAVE;
                        if (!(SEL < func_24B6C8(COLORS))) {
                            SEL = func_24B6C8(COLORS) - 1;
                        }
                    }
                    break;
                case 2:
                    if (*(s32 *)ENTRY == 0x82) {
                        TAIL(0, 7);
                    } else if (!(FLAGS & 0xC000)) {
                        FLAGS |= (u32)0x4000 << PL;
                        TAIL(0, 1);
                    }
                    break;
                default:
                    break;
                }
                break;
            }
            /* held 0x1000: cancel */
            if (pad[0] & 0x1000) {
                if (FLAGS & BIT(0x1000)) {
                    FLAGS ^= BIT(0x1000);
                    if (FLAGS & BIT(0x100000)) {
                        func_26EB78(M + 40 * PL + 0xC8, D_0042DEE0);
                    } else {
                        func_26EB78(M + 40 * PL + 0xC8, D_0042DF00);
                    }
                    CLEAR_IF_SET(BIT(0x100000));
                    CLEAR_IF_SET(BIT(0x40000));
                    CLEAR_IF_SET(BIT(0x100));
                    CLEAR_IF_SET(BIT(0x400));
                    TAIL(0, 2);
                    break;
                }
                if (*(s32 *)(M + 0x36C4) != 1) {
                    *(s32 *)(M + 0x36D0) = 0;
                }
                if (FLAGS & BIT(0x400)) {
                    func_26EA88(M + 40 * PL + 0x78);
                    CLEAR_IF_SET(BIT(0x100000));
                    CLEAR_IF_SET(BIT(0x1000));
                    CLEAR_IF_SET(BIT(0x40000));
                    CLEAR_IF_SET(BIT(0x100));
                    CLEAR_IF_SET(BIT(0x400));
                    TAIL(0, 2);
                    break;
                }
                if ((FLAGS & 0xC0) != 0xC0) {
                    break;
                }
                func_00407BC0();
                *out = 0;
                func_00297FE0(0, 2, 64, 64, 1);
                break;
            }
        } while (0);
        if (doTail) {
            func_00297FE0(ta, tb, 64, 64, 1);
        }
    }
    return 0;
}
