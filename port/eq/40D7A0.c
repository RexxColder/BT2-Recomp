#include "common.h"

/* Frontend reel / colour select (player-1/2 variant of 0x414DE8). G = *D_0042BB78 is the menu state; i is the local pad
 * index, the real player is P = i + G->0x37CC. Per-player words at G + 4P + off, per-(player,stage) words at G + 20P + 4*depth + off.
 *   0x240 flags (<<P): 0x100 locked, 0x400 done, 0x1000 type select active, 0x4000 pending, 0x40000/0x100000 colour
 *   0x2BC reel cursor  0x2C4 colour cursor  0x2CC reel count  0x2D4 colour count  0x2DC depth (0..5)
 *   0x2E4/0x30C/0x334 chosen id / reel / colour [P][depth]   0x360 table of 44-byte entries (7 per row)
 *   0x338C per-cell value, 134 words per player   0x35C entry count   0x37BC.. globals   pad table D_003B0B00 + 0x134, 0x180 per pad */
extern u8 *D_0042BB78 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

extern s32 func_0026EB60(s32 arg0);
extern void func_0026EB78(u8 *arg0, const char *arg1);
extern s32 func_0026EA88(u8 *arg0);
extern s32 func_0024AD60(u8 *arg0, s32 *arg1, s32 arg2);
extern s32 func_0024ACE8(u8 *arg0, s32 *arg1, s32 arg2);
extern void func_0024AEA0(u8 *arg0, s32 *arg1, s32 *arg2, s32 arg3);
extern void func_0024ADE8(u8 *arg0, s32 *arg1, s32 *arg2, s32 arg3);
extern u8 func_0024B6C8(u32 arg0);
extern s32 func_0024B730(s32 arg0, s32 arg1);
extern void func_0040A710(s32 arg0);
extern void func_0040A7D8(s32 arg0);
extern void func_0040AF10(s32 arg0);
extern void func_0040AF70(s32 arg0);
extern void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
extern void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_00325370();
extern s64 GetTimerSystemTime();
extern s32 rand();

#define G D_0042BB78
#define W(off) (*(s32 *)(G + (off)))
#define FLAGS W(0x240)
#define P (i + W(0x37CC))
#define PW(off) (*(s32 *)(G + 4 * P + (off)))
#define HASBIT(b) ((FLAGS & ((b) << P)) != 0)
#define SETBIT(b) (FLAGS |= (b) << P)
#define CLRBIT(b) (FLAGS &= ~((b) << P))
#define DEPTH PW(0x2DC)
/* cell words of the current (player, depth); the flag 0x400 picks the second bank */
#define CELL(a, b) ((s32 *)(G + 20 * P + 4 * DEPTH + (HASBIT(0x400) ? (a) : (b))))
#define SELP CELL(0x240, 0x244)
#define PAGEP CELL(0x268, 0x26C)
#define CURP CELL(0x290, 0x294)
#define SELFIX ((s32 *)(G + 20 * P + 4 * DEPTH + 0x244))
#define ENTRY(page, sel) (*(u8 **)(G + 4 * P + 0x360) + 44 * (7 * (page) + (sel)))
#define CUR_ENTRY ENTRY(*PAGEP, *SELP)
#define CELLVAL (*(s32 *)(G + 0x338C + 4 * (7 * *PAGEP + 134 * P + *SELP)))
#define CHOICE(base, d) (*(s32 *)(G + (base) + 4 * (5 * P + (d))))
#define REDRAW(a, b) func_00297FE0((a), (b), 64, 64, 1)

/* One pad of the menu. outFlag is the caller's pointer cleared when leaving the whole menu. */
static void PadStep(s32 *outFlag, s32 i, u8 *pad) {
    u32 btn = *(u32 *)(pad + 0x10);

    /* 0x80: previous cell / colour */
    if ((btn & 0x80) && !HASBIT(0x100)) {
        if (HASBIT(0x1000)) {
            s32 r;
            s32 adj;
            if (!HASBIT(0x100000)) return;
            r = PW(0x2C4) % 3;
            adj = r - 1;
            if (adj < 0) adj = 2;
            PW(0x2C4) = PW(0x2C4) - r + adj;
            if (PW(0x2C4) >= PW(0x2D4)) PW(0x2C4) = PW(0x2D4) - 1;
            REDRAW(0, 0);
            return;
        }
        func_0040AF10(P);
        CELLVAL = *CURP;
        func_0024AD60(*(u8 **)(G + 4 * P + 0x360), SELFIX, *PAGEP);
        *CURP = *(s32 *)(G + 0x338C + 4 * (7 * *PAGEP + 134 * P + *SELP));
        REDRAW(0, 8);
        return;
    }
    /* 0x20: next cell / colour */
    if ((btn & 0x20) && !HASBIT(0x100)) {
        if (HASBIT(0x1000)) {
            s32 c;
            if (!HASBIT(0x100000)) return;
            c = PW(0x2C4);
            PW(0x2C4) = c - c % 3 + (c % 3 + 1) % 3;
            c = PW(0x2C4);
            if (c >= PW(0x2D4)) PW(0x2C4) = c - c % 3;
            REDRAW(0, 0);
            return;
        }
        func_0040AF10(P);
        CELLVAL = *CURP;
        func_0024ACE8(*(u8 **)(G + 4 * P + 0x360), SELFIX, *PAGEP);
        *CURP = *(s32 *)(G + 0x338C + 4 * (7 * *PAGEP + 134 * P + *SELP));
        REDRAW(0, 8);
        return;
    }
    /* 0x10: up */
    if ((btn & 0x10) && !HASBIT(0x100)) {
        if (HASBIT(0x1000)) {
            if (!HASBIT(0x100000)) {
                PW(0x2BC)--;
                if (PW(0x2BC) < 0) PW(0x2BC) = PW(0x2CC) - 1;
                REDRAW(0, 0);
                return;
            }
            PW(0x2C4) -= 3;
            if (PW(0x2C4) < 0) {
                PW(0x2C4) += 6;
                while (!(PW(0x2C4) < PW(0x2D4))) PW(0x2C4) -= 3;
            }
            if (PW(0x2D4) >= 4) REDRAW(0, 0);
            return;
        }
        if (W(0x37BC) >= 2) {
            func_0040AF10(P);
            CELLVAL = *CURP;
            func_0024AEA0(*(u8 **)(G + 4 * P + 0x360), SELFIX, PAGEP, W(0x37BC));
            *CURP = *(s32 *)(G + 0x338C + 4 * (7 * *PAGEP + 134 * P + *SELP));
            func_0040A710(P);
            func_0026EB78(G + 40 * P + 120, "fr_reel_up");
            REDRAW(1, 2);
        }
        return;
    }
    /* 0x40: down */
    if ((btn & 0x40) && !HASBIT(0x100)) {
        if (HASBIT(0x1000)) {
            if (!HASBIT(0x100000)) {
                PW(0x2BC)++;
                if (PW(0x2CC) - 1 < PW(0x2BC)) PW(0x2BC) = 0;
                REDRAW(0, 0);
                return;
            }
            PW(0x2C4) += 3;
            if (PW(0x2C4) >= PW(0x2D4)) PW(0x2C4) = PW(0x2C4) % 3;
            if (PW(0x2D4) >= 4) REDRAW(0, 0);
            return;
        }
        if (W(0x37BC) >= 2) {
            func_0040AF10(P);
            CELLVAL = *CURP;
            func_0024ADE8(*(u8 **)(G + 4 * P + 0x360), SELFIX, PAGEP, W(0x37BC));
            *CURP = *(s32 *)(G + 0x338C + 4 * (7 * *PAGEP + 134 * P + *SELP));
            func_0040A710(P);
            func_0026EB78(G + 40 * P + 120, "fr_reel_down");
            REDRAW(1, 2);
        }
        return;
    }
    /* 0x400: previous variant of the current entry */
    if ((btn & 0x400) && !HASBIT(0x100)) {
        if (HASBIT(0x1000)) return;
        if (*(s32 *)(CUR_ENTRY + 4) == 0) return;
        func_0040AF10(P);
        *CURP = *CURP - 1;
        if (*CURP < 0) *CURP = *(s32 *)(CUR_ENTRY + 4) - 1;
        CELLVAL = *CURP;
        func_0040AF70(P);
        REDRAW(0, 0);
        return;
    }
    /* 0x800: next variant of the current entry */
    if ((btn & 0x800) && !HASBIT(0x100)) {
        if (HASBIT(0x1000)) return;
        if (*(s32 *)(CUR_ENTRY + 4) == 0) return;
        func_0040AF10(P);
        *CURP = *CURP + 1;
        if (*(s32 *)(CUR_ENTRY + 4) - 1 < *CURP) *CURP = 0;
        CELLVAL = *CURP;
        func_0040AF70(P);
        REDRAW(0, 0);
        return;
    }
    /* 0x8000: done */
    if ((*(u32 *)pad & 0x8000) && !HASBIT(0x100)) {
        if (HASBIT(0x1000)) return;
        if (DEPTH != 0) {
            func_0026EB78(G + 40 * P + 120, "fr_out");
            SETBIT(0x100);
            SETBIT(0x400);
            W(0x37D0) = 15;
            func_0040AF10(P);
            if (W(0x37C8) != 1) W(0x37CC) = 1;
            REDRAW(0, 1);
        } else {
            REDRAW(0, 7);
        }
        return;
    }
    /* 0x4000: confirm */
    if ((*(u32 *)pad & 0x4000) && !HASBIT(0x100)) {
        if (!HASBIT(0x1000)) {
            /* pick the entry: refuse one already chosen at an earlier depth */
            s32 dup = 0;
            if (*(s32 *)CUR_ENTRY != 130) {
                s32 k = 0;
                if (DEPTH > 0) {
                    do {
                        s32 other = CHOICE(0x2E4, k);
                        k++;
                        if (func_0024B730(*(s32 *)CUR_ENTRY, other)) dup = 1;
                    } while (k < DEPTH);
                }
            }
            if (dup) {
                REDRAW(0, 7);
                return;
            }
            SETBIT(0x1000);
            PW(0x2BC) = CHOICE(0x30C, DEPTH);
            if (*SELP + 7 * *PAGEP < 74) {
                if (*(s32 *)CUR_ENTRY == 130) {
                    PW(0x2CC) = 2;
                    if (PW(0x2BC) == 2) PW(0x2BC) = 0;
                } else {
                    PW(0x2CC) = 3;
                }
                func_0026EB78(G + 40 * P + 200, "fr_type_in");
                REDRAW(1, 0);
            } else {
                SETBIT(0x40000);
                SETBIT(0x1000);
                SETBIT(0x100000);
                PW(0x2BC) = 1;
                func_0026EB78(G + 40 * P + 200, "fr_color_select_in");
                PW(0x2D4) = func_0024B6C8(*(s32 *)CUR_ENTRY);
                PW(0x2C4) = CHOICE(0x334, DEPTH);
                if (PW(0x2C4) >= PW(0x2D4)) PW(0x2C4) = PW(0x2D4) - 1;
                REDRAW(0, 1);
            }
            return;
        }
        if (HASBIT(0x100000)) {
            /* colour chosen: store the pick and move to the next depth */
            REDRAW(0, 1);
            CLRBIT(0x1000);
            CLRBIT(0x100000);
            func_0026EB78(G + 40 * P + 200, "fr_color_select_out");
            CHOICE(0x2E4, DEPTH) = *(s32 *)CUR_ENTRY;
            CHOICE(0x30C, DEPTH) = PW(0x2BC);
            CHOICE(0x334, DEPTH) = PW(0x2C4);
            DEPTH++;
            func_0040A7D8(P);
            if (DEPTH != 5) {
                func_0040AF70(P);
                func_0040AF10(P);
                func_0040A710(P);
                return;
            }
            goto all_picked;
        }
        /* type select: which reel was picked (PW(0x2BC)) */
        {
            s32 reel = PW(0x2BC);
            if (reel == 1) {
                SETBIT(0x40000);
            } else if (reel >= 2) {
                if (reel != 2) return;
                if (*(s32 *)CUR_ENTRY != 130) {
                    if ((FLAGS & 0xC000) == 0) {
                        SETBIT(0x4000);
                        REDRAW(0, 1);
                    }
                    return;
                }
                REDRAW(0, 7);
                return;
            } else if (reel != 0) {
                return;
            }
        }
        REDRAW(0, 1);
        if (*(s32 *)CUR_ENTRY == 130) {
            /* random pick */
            s32 dup = 0;
            s32 id;
            s32 r;
            s32 k;
            CLRBIT(0x1000);
            CLRBIT(0x100000);
            func_0026EB78(G + 40 * P + 200, "fr_type_out");
            func_00325370((s32)GetTimerSystemTime());
            for (;;) {
                u8 *e;
                do {
                    r = rand() % W(0x35C);
                    id = *(s32 *)(*(u8 **)(G + 4 * P + 0x360) + 44 * r);
                } while (id >= 130);
                e = *(u8 **)(G + 4 * P + 0x360) + 44 * r;
                if (*(s32 *)(e + 4) != 0) {
                    s32 rr = rand();
                    e = *(u8 **)(G + 4 * P + 0x360) + 44 * r;
                    id = *(s32 *)(e + 8 + 4 * (rr % *(s32 *)(e + 4)));
                }
                k = 0;
                if (DEPTH > 0) {
                    do {
                        s32 other = CHOICE(0x2E4, k);
                        k++;
                        if (func_0024B730(id, other)) dup = 1;
                    } while (k < DEPTH);
                }
                if (!dup) break;
                dup = 0;
            }
            CHOICE(0x2E4, DEPTH) = id;
            CHOICE(0x30C, DEPTH) = PW(0x2BC);
            {
                s32 rnd = rand();
                s32 cnt = func_0024B6C8(id);
                CHOICE(0x334, DEPTH) = rnd % cnt;
                DEPTH++;
            }
            func_0040A7D8(P);
            if (DEPTH != 5) {
                func_0040AF70(P);
                func_0040AF10(P);
                func_0040A710(P);
                return;
            }
            goto all_picked;
        }
        SETBIT(0x100000);
        func_0026EB78(G + 40 * P + 200, "fr_color_select");
        PW(0x2D4) = func_0024B6C8(*(s32 *)CUR_ENTRY);
        PW(0x2C4) = CHOICE(0x334, DEPTH);
        if (PW(0x2C4) >= PW(0x2D4)) PW(0x2C4) = PW(0x2D4) - 1;
        return;
    all_picked:
        func_0026EB78(G + 40 * P + 120, "fr_out");
        SETBIT(0x100);
        SETBIT(0x400);
        W(0x37D0) = 15;
        if (W(0x37C8) != 1) W(0x37CC) = 1;
        return;
    }
    /* 0x1000: back */
    if (!(*(u32 *)pad & 0x1000)) return;
    if (HASBIT(0x1000)) {
        FLAGS ^= 0x1000 << P;
        if (HASBIT(0x100000)) {
            func_0026EB78(G + 40 * P + 200, "fr_color_select_out");
        } else {
            func_0026EB78(G + 40 * P + 200, "fr_type_out");
        }
        CLRBIT(0x100000);
        CLRBIT(0x40000);
    } else if (HASBIT(0x400)) {
        func_0026EA88(G + 40 * P + 120);
        if (DEPTH == 5) {
            DEPTH = 4;
            func_0040A7D8(P);
        } else {
            func_0040AF10(P);
        }
        CLRBIT(0x100000);
        CLRBIT(0x1000);
        CLRBIT(0x40000);
        CLRBIT(0x100);
        CLRBIT(0x400);
    } else {
        s32 d = DEPTH;
        if (d == 0) {
            if (W(0x37C8) != 1) W(0x37CC) = 0;
            if (HASBIT(0x400)) {
                func_0026EA88(G + 40 * P + 120);
                if (DEPTH == 5) {
                    DEPTH = 4;
                    func_0040A7D8(P);
                } else {
                    func_0040AF10(P);
                }
                CLRBIT(0x100000);
                CLRBIT(0x1000);
                CLRBIT(0x40000);
                CLRBIT(0x100);
                CLRBIT(0x400);
            } else if (W(0x37C4) == 4) {
                func_00243A80(0, 0, 0);
                *outFlag = 0;
            }
            REDRAW(0, 2);
            return;
        }
        DEPTH = d - 1;
        func_0040AF70(P);
        func_0040AF10(P);
        func_0040A710(P);
        func_0040A7D8(P);
    }
    REDRAW(0, 2);
}

s32 func_0040D7A0(s32 *outFlag) {
    s32 n = 0;
    s32 i;
    u8 *pad;
    s32 mode;

    if (func_0026EB60((s32)(G + 0x50)) == 0) return 0;
    mode = W(0x37C8);
    if (mode == 1) {
        n = 2;
    } else if (mode == 0 || mode == 2) {
        n = 1;
    } else {
        return mode < 2 ? 1 : 2;
    }
    pad = D_003B0B00 + 0x134;
    for (i = 0; i < n; i++, pad += 0x180) PadStep(outFlag, i, pad);
    return 0;
}
