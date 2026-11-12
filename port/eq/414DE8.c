#include "common.h"

extern u8 *D_0042BB7C __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern char D_0042EC98[], D_0042ECA8[], D_0042ECB8[], D_0042ECD0[], D_0042ECD8[], D_0042ECE8[], D_0042ECF8[], D_0042ED10[];

extern s32 func_0026EB60(s32 arg0);
extern void func_0026EB78(u8 *arg0, const char *arg1);
extern s32 func_0026EA88(u8 *arg0);
extern s32 func_0024AD60(u8 *arg0, s32 *arg1, s32 arg2);
extern s32 func_0024ACE8(u8 *arg0, s32 *arg1, s32 arg2);
extern void func_0024AEA0(u8 *arg0, s32 *arg1, s32 *arg2, s32 arg3);
extern void func_0024ADE8(u8 *arg0, s32 *arg1, s32 *arg2, s32 arg3);
extern u8 func_0024B6C8(u32 arg0);
extern void func_00412970(s32 arg0);
extern void func_004120D0(s32 arg0);
extern void func_00412A10(s32 arg0);
extern void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
extern void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_00325370();
extern s64 GetTimerSystemTime();
extern s32 rand();

/* Menu state G = *D_0042BB7C (a "frontend reel/colour select" screen for up to 2 players; i = local pad index, the
 * real player is P = i + G->0x3744). Per-player words at G + 4P + off, per-(player,stage) words at G + 8P + 4s + off.
 *   0x238 flags (<<P): 0x100 locked, 0x400 done, 0x1000 type-select active, 0x4000 pending, 0x40000/0x100000 colour
 *   0x23C/0x24C cell column/row [P][s]   0x25C cursor [P][s]   0x26C chosen entry id [P][s]
 *   0x27C item index   0x284 colour index   0x28C item count   0x294 colour count   0x29C stage 0..2
 *   0x2A4/0x2B4/0x2C4 saved choice [P][stage]   0x2D4 entry count   0x2D8 entry table (44-byte entries, 7 per row)
 *   0x3304 per-cell value, 134 words per player   0x3734/0x373C/0x3740/0x3744/0x3748 globals */
#define G D_0042BB7C
#define W(off) (*(s32 *)(G + (off)))
#define FLAGS W(0x238)
#define P (i + W(0x3744))
#define PW(off) (*(s32 *)(G + 4 * P + (off)))
#define STAGE PW(0x29C)
#define SEL (STAGE < 2 ? STAGE : 1)
#define PS(off, s) (*(s32 *)(G + 8 * P + 4 * (s) + (off)))
#define COL(s) PS(0x23C, s)
#define ROW(s) PS(0x24C, s)
#define CUR(s) PS(0x25C, s)
#define CHOSEN(s) PS(0x26C, s)
#define CELL(s) (*(s32 *)(G + 0x3304 + 4 * (7 * ROW(s) + 134 * P + COL(s))))
#define TABLE (*(u8 **)(G + 0x2D8 + 4 * P))
#define ENTRY(s) (TABLE + 44 * (7 * ROW(s) + COL(s)))
#define SETBIT(b) (FLAGS |= (b) << P)
#define CLRBIT(b) (FLAGS &= ~((b) << P))
#define HASBIT(b) ((FLAGS & ((b) << P)) != 0)

/* Shared tail of both "confirm" paths: after the stage counter was bumped, stage 2 means this player is finished. */
static void AdvanceStage(s32 i) {
    if (STAGE == 2) {
        func_0026EB78(G + 40 * P + 0x88, D_0042ECD0); /* "fr_out" */
        FLAGS |= 0x100 << P;
        FLAGS |= 0x400 << P;
        W(0x3748) = 15;
        if (W(0x3740) != 1) {
            W(0x3744) = 1;
        }
    } else {
        func_00412A10(P);
        func_00412970(P);
        func_004120D0(P);
    }
}

s32 func_00414DE8(s32 *done) {
    s32 nplayers;
    s32 i;
    s32 sel;
    s32 n;
    s32 r;
    s32 *pad;

    nplayers = 0;
    if (func_0026EB60(W(0) + 0x60) == 0) {
        return 0;
    }
    if (W(0x3740) == 1) {
        nplayers = 2;
    } else if (W(0x3740) == 0 || W(0x3740) == 2) {
        nplayers = 1;
    } else if (W(0x3740) < 0) {
        return 1;
    } else {
        return 2;
    }
    if (nplayers == 0) {
        return 0;
    }

    pad = (s32 *)(D_003B0B00 + 0x134);
    for (i = 0; i < nplayers; i++, pad += 0x60) {
        /* 0x80: previous cell / colour */
        if ((pad[4] & 0x80) && !HASBIT(0x100)) {
            if (!HASBIT(0x1000)) {
                func_00412970(P);
                sel = SEL;
                CELL(sel) = CUR(sel);
                sel = STAGE < 2 ? STAGE : 1;
                func_0024AD60(TABLE, &COL(STAGE), ROW(SEL));
                CUR(SEL) = CELL(SEL);
                CHOSEN(STAGE) = *(s32 *)ENTRY(SEL);
                func_00297FE0(0, 8, 64, 64, 1);
                continue;
            }
            if (!HASBIT(0x100000)) {
                continue;
            }
            n = PW(0x284) % 3;
            r = n - 1;
            if (r < 0) {
                r = 2;
            }
            PW(0x284) = PW(0x284) - n + r;
            if (PW(0x284) >= PW(0x294)) {
                PW(0x284) = PW(0x294) - 1;
            }
            func_00297FE0(0, 0, 64, 64, 1);
            continue;
        }
        /* 0x20: next cell / colour */
        if ((pad[4] & 0x20) && !HASBIT(0x100)) {
            if (!HASBIT(0x1000)) {
                func_00412970(P);
                sel = SEL;
                CELL(sel) = CUR(sel);
                func_0024ACE8(TABLE, &COL(STAGE), ROW(SEL));
                CUR(SEL) = CELL(SEL);
                CHOSEN(STAGE) = *(s32 *)ENTRY(SEL);
                func_00297FE0(0, 8, 64, 64, 1);
                continue;
            }
            if (!HASBIT(0x100000)) {
                continue;
            }
            n = PW(0x284) % 3;
            PW(0x284) = PW(0x284) - n + (n + 1) % 3;
            if (PW(0x284) >= PW(0x294)) {
                PW(0x284) = PW(0x284) - PW(0x284) % 3;
            }
            func_00297FE0(0, 0, 64, 64, 1);
            continue;
        }
        /* 0x10: previous row / item */
        if ((pad[4] & 0x10) && !HASBIT(0x100)) {
            if (!HASBIT(0x1000)) {
                if (W(0x3734) < 2) {
                    continue;
                }
                func_00412970(P);
                sel = SEL;
                CELL(sel) = CUR(sel);
                func_0024AEA0(TABLE, &COL(STAGE), &ROW(SEL), W(0x3734));
                sel = SEL;
                CUR(sel) = CELL(sel);
                func_004120D0(P);
                CHOSEN(STAGE) = *(s32 *)ENTRY(SEL);
                func_0026EB78(G + 40 * P + 0x88, D_0042EC98); /* "fr_reel_up" */
                func_00297FE0(1, 2, 64, 64, 1);
                continue;
            }
            if (!HASBIT(0x100000)) {
                PW(0x27C)--;
                if (PW(0x27C) < 0) {
                    PW(0x27C) = PW(0x28C) - 1;
                }
                func_00297FE0(0, 0, 64, 64, 1);
                continue;
            }
            PW(0x284) -= 3;
            if (PW(0x284) < 0) {
                PW(0x284) += 6;
                while (PW(0x284) >= PW(0x294)) {
                    PW(0x284) -= 3;
                }
            }
            if (PW(0x294) < 4) {
                continue;
            }
            func_00297FE0(0, 0, 64, 64, 1);
            continue;
        }
        /* 0x40: next row / item */
        if ((pad[4] & 0x40) && !HASBIT(0x100)) {
            if (!HASBIT(0x1000)) {
                if (W(0x3734) < 2) {
                    continue;
                }
                func_00412970(P);
                sel = SEL;
                CELL(sel) = CUR(sel);
                func_0024ADE8(TABLE, &COL(STAGE), &ROW(SEL), W(0x3734));
                sel = SEL;
                CUR(sel) = CELL(sel);
                func_004120D0(P);
                CHOSEN(STAGE) = *(s32 *)ENTRY(SEL);
                func_0026EB78(G + 40 * P + 0x88, D_0042ECA8); /* "fr_reel_down" */
                func_00297FE0(1, 2, 64, 64, 1);
                continue;
            }
            if (!HASBIT(0x100000)) {
                PW(0x27C)++;
                if (PW(0x28C) - 1 < PW(0x27C)) {
                    PW(0x27C) = 0;
                }
                func_00297FE0(0, 0, 64, 64, 1);
                continue;
            }
            PW(0x284) += 3;
            if (PW(0x284) >= PW(0x294)) {
                PW(0x284) = PW(0x284) % 3;
            }
            if (PW(0x294) < 4) {
                continue;
            }
            func_00297FE0(0, 0, 64, 64, 1);
            continue;
        }
        /* 0x400: cursor back inside the row's entry */
        if ((pad[4] & 0x400) && !HASBIT(0x100)) {
            if (HASBIT(0x1000) || *(s32 *)(ENTRY(SEL) + 4) == 0) {
                continue;
            }
            func_00412970(P);
            CUR(SEL)--;
            if (CUR(SEL) < 0) {
                CUR(SEL) = *(s32 *)(ENTRY(SEL) + 4) - 1;
            }
            CELL(SEL) = CUR(SEL);
            func_00412A10(P);
            CHOSEN(STAGE) = *(s32 *)ENTRY(SEL);
            func_00297FE0(0, 0, 64, 64, 1);
            continue;
        }
        /* 0x800: cursor forward inside the row's entry */
        if ((pad[4] & 0x800) && !HASBIT(0x100)) {
            if (HASBIT(0x1000) || *(s32 *)(ENTRY(SEL) + 4) == 0) {
                continue;
            }
            func_00412970(P);
            CUR(SEL)++;
            if (*(s32 *)(ENTRY(SEL) + 4) - 1 < CUR(SEL)) {
                CUR(SEL) = 0;
            }
            CELL(SEL) = CUR(SEL);
            func_00412A10(P);
            CHOSEN(STAGE) = *(s32 *)ENTRY(SEL);
            func_00297FE0(0, 0, 64, 64, 1);
            continue;
        }
        /* 0x4000: confirm */
        if ((pad[4] & 0x4000) && !HASBIT(0x100)) {
            if (!HASBIT(0x1000)) {
                /* open the type/colour screen for the current item */
                FLAGS |= 0x1000 << P;
                PW(0x27C) = *(s32 *)(G + 4 * (2 * P + STAGE) + 0x2B4);
                if (COL(SEL) + 7 * ROW(SEL) < 74) {
                    if (*(s32 *)ENTRY(SEL) == 130) {
                        PW(0x28C) = 2;
                        if (PW(0x27C) == 2) {
                            PW(0x27C) = 0;
                        }
                    } else {
                        PW(0x28C) = 3;
                    }
                    func_0026EB78(G + 40 * P + 0xD8, D_0042ED10); /* "fr_type_in" */
                    func_00297FE0(1, 0, 64, 64, 1);
                } else {
                    FLAGS |= 0x40000 << P;
                    FLAGS |= 0x1000 << P;
                    FLAGS |= 0x100000 << P;
                    PW(0x27C) = 1;
                    func_0026EB78(G + 40 * P + 0xD8, D_0042ECF8); /* "fr_color_select_in" */
                    PW(0x294) = func_0024B6C8(*(s32 *)ENTRY(SEL));
                    PW(0x284) = *(s32 *)(G + 4 * (2 * P + STAGE) + 0x2C4);
                    if (PW(0x284) >= PW(0x294)) {
                        PW(0x284) = PW(0x294) - 1;
                    }
                    func_00297FE0(0, 1, 64, 64, 1);
                }
                continue;
            }
            if (HASBIT(0x100000)) {
                /* colour chosen */
                func_00297FE0(0, 1, 64, 64, 1);
                CLRBIT(0x1000);
                CLRBIT(0x100000);
                func_0026EB78(G + 40 * P + 0xD8, D_0042ECB8); /* "fr_color_select_out" */
                *(s32 *)(G + 4 * (2 * P + STAGE) + 0x2A4) = *(s32 *)ENTRY(SEL);
                *(s32 *)(G + 4 * (2 * P + STAGE) + 0x2B4) = PW(0x27C);
                *(s32 *)(G + 4 * (2 * P + STAGE) + 0x2C4) = PW(0x284);
                STAGE++;
                AdvanceStage(i);
                continue;
            }
            if (PW(0x27C) == 0 || PW(0x27C) == 1 || PW(0x27C) == 2) {
                if (PW(0x27C) == 2) {
                    if (*(s32 *)ENTRY(SEL) == 130) {
                        func_00297FE0(0, 7, 64, 64, 1);
                    } else if ((FLAGS & 0xC000) == 0) {
                        FLAGS |= 0x4000 << P;
                        func_00297FE0(0, 1, 64, 64, 1);
                    }
                    continue;
                }
                if (PW(0x27C) == 1) {
                    FLAGS |= 0x40000 << P;
                }
                func_00297FE0(0, 1, 64, 64, 1);
                if (*(s32 *)ENTRY(SEL) == 130) {
                    /* random item: pick a random entry below id 130, then a random variant */
                    s32 id;
                    s32 ent;
                    s32 ncol;

                    CLRBIT(0x1000);
                    CLRBIT(0x100000);
                    func_0026EB78(G + 40 * P + 0xD8, D_0042ECD8); /* "fr_type_out" */
                    func_00325370((s32)GetTimerSystemTime());
                    do {
                        ent = (rand() % W(0x2D4)) * 44;
                        id = *(s32 *)(TABLE + ent);
                    } while (id >= 130);
                    if (*(s32 *)(TABLE + ent + 4) != 0) {
                        id = *(s32 *)(TABLE + ent + 8 + 4 * (rand() % *(s32 *)(TABLE + ent + 4)));
                    }
                    *(s32 *)(G + 4 * (2 * P + STAGE) + 0x2A4) = id;
                    *(s32 *)(G + 4 * (2 * P + STAGE) + 0x2B4) = PW(0x27C);
                    ncol = rand();
                    *(s32 *)(G + 4 * (2 * P + STAGE) + 0x2C4) = ncol % func_0024B6C8(id);
                    STAGE++;
                    AdvanceStage(i);
                } else {
                    FLAGS |= 0x100000 << P;
                    func_0026EB78(G + 40 * P + 0xD8, D_0042ECE8); /* "fr_color_select" */
                    PW(0x294) = func_0024B6C8(*(s32 *)ENTRY(SEL));
                    PW(0x284) = *(s32 *)(G + 4 * (2 * P + STAGE) + 0x2C4);
                    if (PW(0x284) >= PW(0x294)) {
                        PW(0x284) = PW(0x294) - 1;
                    }
                }
            }
            continue;
        }
        /* 0x1000: cancel / back */
        if (!(pad[4] & 0x1000)) {
            continue;
        }
        if (HASBIT(0x1000)) {
            CLRBIT(0x1000);
            if (HASBIT(0x100000)) {
                func_0026EB78(G + 40 * P + 0xD8, D_0042ECB8); /* "fr_color_select_out" */
            } else {
                func_0026EB78(G + 40 * P + 0xD8, D_0042ECD8); /* "fr_type_out" */
            }
            CLRBIT(0x100000);
            CLRBIT(0x40000);
        } else if (HASBIT(0x400)) {
            func_0026EA88(G + 40 * P + 0x88);
            if (STAGE == 2) {
                STAGE = 1;
            }
            CLRBIT(0x100000);
            CLRBIT(0x1000);
            CLRBIT(0x40000);
            CLRBIT(0x100);
            CLRBIT(0x400);
        } else if (STAGE != 0) {
            PW(0x22C) &= ~(0x40 << STAGE);
            STAGE--;
            func_00412A10(P);
            func_004120D0(P);
        } else {
            if (W(0x3740) != 1) {
                W(0x3744) = 0;
            }
            if (HASBIT(0x400)) {
                func_0026EA88(G + 40 * P + 0x88);
                if (STAGE == 2) {
                    STAGE = 1;
                }
                CLRBIT(0x100000);
                CLRBIT(0x1000);
                CLRBIT(0x40000);
                CLRBIT(0x100);
                CLRBIT(0x400);
            } else if (W(0x373C) == 4) {
                func_00243A80(0, 0, 0);
                *done = 0;
            }
            func_00297FE0(0, 2, 64, 64, 1);
            continue;
        }
        func_00297FE0(0, 2, 64, 64, 1);

    }
    return 0;
}
