#include "common.h"

/* Menu overlay: character-select / partner-select pad handling for one player slot.
 * ui = the select-screen state object; p = ui->cur_player; each player owns a column in the
 * s32 arrays below (cursor x/y, sub-cursor, row, selection ...) and bit (n << p) in the state flags. */

extern u8 *D_0042A570;
extern u8 D_003B0B00[];
extern u8 *D_003876A4;

u8 func_0024B6C8(u32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_003F0AA0(s32 arg0);
void func_003F0B00(s32 arg0);
void func_003F0748(s32 arg0);
s32 func_0026EB60(u8 *arg0);
void func_0026EB78(u8 *obj, const char *name);
void func_0026EAE0(u8 *obj, s32 arg1);
void func_0026EA88(u8 *obj);
void func_0024AD60(u8 *arg0, u8 *pos, s32 arg2);
void func_0024ACE8(u8 *arg0, u8 *pos, s32 arg2);
void func_0024AEA0(u8 *arg0, u8 *pos_x, u8 *pos_y, s32 arg3);
void func_0024ADE8(u8 *arg0, u8 *pos_x, u8 *pos_y, s32 arg3);
void func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

#define W(p, off) (*(s32 *)((p) + (off)))
#define PAD_A (*(s32 *)(D_003B0B00 + 0x144)) /* direction buttons */
#define PAD_B (*(s32 *)(D_003B0B00 + 0x134)) /* face buttons */
#define PL W(ui, 0x214)
#define FLG W(ui, 0x218)
#define BIT(n) ((n) << PL)
#define COL(off) W(ui, (off) + 4 * PL) /* per-player s32 */
#define CNT() func_0024B6C8(COL(0x24C))
#define ITEM_LIST() ((u8 *)COL(0x258))
#define CELL() W(ui, 0x3284 + 4 * (7 * COL(0x224) + 134 * PL + COL(0x21C)))
#define ENTRY() (ITEM_LIST() + 44 * (7 * COL(0x224) + COL(0x21C)))
#define ANIM_SLOT() (ui + 0xC4 + 40 * PL)
#define REEL_SLOT() (ui + 0x74 + 40 * PL)

void func_003F25C0(s32 *done) {
    u8 *ui = D_0042A570;
    s32 row;
    s32 sel;
    s32 rem;
    s32 next;

    if (func_0026EB60(ui + 0x4C) == 0) {
        return;
    }

    if ((PAD_A & 0x80) && !(FLG & BIT(0x100))) {
        if (FLG & BIT(0x1000)) {
            if (!(FLG & BIT(0x800000))) {
                return;
            }
            sel = COL(0x23C);
            rem = sel % 3;
            next = rem - 1;
            if (next < 0) {
                next = 2;
            }
            COL(0x23C) = sel - rem + next;
            if (COL(0x23C) >= func_0024B6C8(COL(0x24C))) {
                COL(0x23C) = CNT() - 1;
            }
            func_00297FE0(0, 0, 64, 64, 1);
            return;
        }
        func_003F0AA0(PL);
        CELL() = COL(0x22C);
        func_0024AD60(ITEM_LIST(), ui + 0x21C + 4 * PL, COL(0x224));
        COL(0x22C) = CELL();
        func_00297FE0(0, 8, 64, 64, 1);
        return;
    }

    if ((PAD_A & 0x20) && !(FLG & BIT(0x100))) {
        if (FLG & BIT(0x1000)) {
            if (!(FLG & BIT(0x800000))) {
                return;
            }
            sel = COL(0x23C);
            COL(0x23C) = sel - sel % 3 + (sel % 3 + 1) % 3;
            if (COL(0x23C) >= func_0024B6C8(COL(0x24C))) {
                COL(0x23C) -= COL(0x23C) % 3;
            }
            func_00297FE0(0, 0, 64, 64, 1);
            return;
        }
        func_003F0AA0(PL);
        CELL() = COL(0x22C);
        func_0024ACE8(ITEM_LIST(), ui + 0x21C + 4 * PL, COL(0x224));
        COL(0x22C) = CELL();
        func_00297FE0(0, 8, 64, 64, 1);
        return;
    }

    if ((PAD_A & 0x10) && !(FLG & BIT(0x100))) {
        if (FLG & BIT(0x1000)) {
            if (!(FLG & BIT(0x800000))) {
                COL(0x234) -= 1;
                if (COL(0x234) < 0) {
                    COL(0x234) = 2;
                }
                func_00297FE0(0, 0, 64, 64, 1);
                return;
            }
            COL(0x23C) -= 3;
            sel = COL(0x23C);
            if (sel < 0) {
                COL(0x23C) = sel + 6;
                while (COL(0x23C) >= func_0024B6C8(COL(0x24C))) {
                    COL(0x23C) = COL(0x23C) - 3;
                }
            }
            if (CNT() >= 4) {
                func_00297FE0(0, 0, 64, 64, 1);
            }
            return;
        }
        func_003F0AA0(PL);
        CELL() = COL(0x22C);
        func_0024AEA0(ITEM_LIST(), ui + 0x21C + 4 * PL, ui + 0x224 + 4 * PL, W(ui, 0x36B4));
        COL(0x22C) = CELL();
        func_003F0748(PL);
        func_0026EB78(REEL_SLOT(), "fr_reel_up");
        func_00297FE0(1, 2, 64, 64, 1);
        return;
    }

    if ((PAD_A & 0x40) && !(FLG & BIT(0x100))) {
        if (!(FLG & BIT(0x1000))) {
            func_003F0AA0(PL);
            CELL() = COL(0x22C);
            func_0024ADE8(ITEM_LIST(), ui + 0x21C + 4 * PL, ui + 0x224 + 4 * PL, W(ui, 0x36B4));
            COL(0x22C) = CELL();
            func_003F0748(PL);
            func_0026EB78(REEL_SLOT(), "fr_reel_down");
            func_00297FE0(1, 2, 64, 64, 1);
            return;
        }
        if (!(FLG & BIT(0x800000))) {
            COL(0x234) += 1;
            if (COL(0x234) >= 3) {
                COL(0x234) = 0;
            }
            func_00297FE0(0, 0, 64, 64, 1);
            return;
        }
        COL(0x23C) += 3;
        if (COL(0x23C) >= func_0024B6C8(COL(0x24C))) {
            COL(0x23C) %= 3;
        }
        if (CNT() >= 4) {
            func_00297FE0(0, 0, 64, 64, 1);
        }
        return;
    }

    if ((PAD_A & 0x400) && !(FLG & BIT(0x100))) {
        /* left */
        if (FLG & BIT(0x1000)) {
            return;
        }
        if (W(ENTRY(), 4) == 0) {
            return;
        }
        func_003F0AA0(PL);
        COL(0x22C) -= 1;
        if (COL(0x22C) < 0) {
            COL(0x22C) = W(ENTRY(), 4) - 1;
        }
    } else if ((PAD_A & 0x800) && !(FLG & BIT(0x100))) {
        /* right */
        if (FLG & BIT(0x1000)) {
            return;
        }
        if (W(ENTRY(), 4) == 0) {
            return;
        }
        func_003F0AA0(PL);
        COL(0x22C) += 1;
        if (W(ENTRY(), 4) - 1 < COL(0x22C)) {
            COL(0x22C) = 0;
        }
    } else if ((PAD_B & 0x4000) && !(FLG & BIT(0x100))) {
        /* confirm */
        if (FLG & BIT(0x1000)) {
            if (!(FLG & BIT(0x800000))) {
                row = COL(0x234);
                if (row == 1) {
                    FLG |= BIT(0x40000);
                } else if (row >= 2) {
                    if (row == 2 && !(FLG & 0xC000)) {
                        FLG |= BIT(0x4000);
                        func_00297FE0(0, 1, 64, 64, 1);
                    }
                    return;
                } else if (row != 0) {
                    return;
                }
                func_00297FE0(0, 1, 64, 64, 1);
                FLG |= BIT(0x800000);
                func_0026EB78(ANIM_SLOT(), "fr_color_select");
                COL(0x23C) = COL(0x244);
                if (COL(0x23C) >= func_0024B6C8(COL(0x24C))) {
                    COL(0x23C) = CNT() - 1;
                }
                return;
            }
            func_00297FE0(0, 1, 64, 64, 1);
            FLG |= BIT(0x100);
            FLG |= BIT(0x400);
            FLG |= BIT(0x800000);
            W(ui, 0x36C4) = 15;
            func_0026EB78(ANIM_SLOT(), "fr_color_select_out");
            FLG &= (-4097 << PL);
            FLG &= (-8388609 << PL);
            COL(0x244) = COL(0x23C);
            if (PL != 0) {
                return;
            }
        } else {
            FLG |= BIT(0x1000);
            if (W(W(ui, 0x36D0) + 56 * W(D_003876A4, 100), 12) != 3) {
                func_0026EB78(ANIM_SLOT(), "fr_type_in");
                func_00297FE0(1, 0, 64, 64, 1);
                return;
            }
            FLG |= BIT(0x100);
            FLG |= BIT(0x400);
            W(ui, 0x36C4) = 15;
            func_00297FE0(0, 1, 64, 64, 1);
            if (PL != 0) {
                return;
            }
        }
        if (W(W(ui, 0x36D0) + 56 * W(D_003876A4, 100), 12) == 2) {
            PL = 1;
            func_0026EB78(ui + 0x4C, "fr_partnerselect");
            func_0026EAE0(ui + 0x9C, 60);
            func_0026EA88(ui + 0x9C);
            func_002493C0(0, 14246, 15295, 0, 14);
        }
        return;
    } else {
        /* cancel */
        if (!(PAD_B & 0x1000)) {
            return;
        }
        if (FLG & BIT(0x1000)) {
            if (FLG & BIT(0x40000)) {
                FLG ^= BIT(0x40000);
            }
            if (FLG & BIT(0x100)) {
                FLG ^= BIT(0x100);
            }
            if (FLG & BIT(0x400)) {
                FLG ^= BIT(0x400);
            }
            func_00297FE0(0, 2, 64, 64, 1);
            if (FLG & BIT(0x800000)) {
                func_0026EB78(ANIM_SLOT(), "fr_color_select_out");
            } else {
                func_0026EB78(ANIM_SLOT(), "fr_type_out");
            }
            FLG &= (-4097 << PL);
            FLG &= (-8388609 << PL);
            return;
        }
        PL = 0;
        if (!(FLG & 0x400)) {
            if (W(ui, 0x36B8) == 4) {
                W(ui, 0x36CC) = 1;
                *done = 0;
                func_00297FE0(0, 2, 64, 64, 1);
            }
            return;
        }
        func_0026EB78(ui + 0x4C, "fr_partnerselect_out");
        func_0026EB78(ui + 0x9C, "fr_out");
        if (FLG & BIT(0x1000)) {
            FLG ^= BIT(0x1000);
        }
        if (FLG & BIT(0x40000)) {
            FLG ^= BIT(0x40000);
        }
        if (FLG & BIT(0x100)) {
            FLG ^= BIT(0x100);
        }
        if (FLG & BIT(0x400)) {
            FLG ^= BIT(0x400);
        }
        func_00297FE0(0, 2, 64, 64, 1);
        return;
    }
    func_003F0B00(PL);
    func_00297FE0(0, 0, 64, 64, 1);
}
