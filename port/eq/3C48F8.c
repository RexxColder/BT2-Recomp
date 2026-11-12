#include "common.h"

/* Menu state block: pointer stored at D_00421CF4 (re-read after every call, as in the original). */
extern u8 *D_00421CF4 __attribute__((section(".data")));
extern s8 D_00421CA0[] __attribute__((section(".data")));   /* character grid: [page * 42 + row * 14 + col] */
extern u8 *D_00387F2C __attribute__((section(".data")));    /* save-slot table base */
extern u8 D_3B0B00[];                                        /* pad state; +0x134 and +0x144 are button words */
extern char D_00423068[], D_00423078[], D_00423088[], D_00423098[], D_004230B0[];

s32 func_26EB60(void *obj);
void func_26EB78(void *obj, char *name);
void func_26EAE0(void *obj, s32 arg1);
void func_26EA88(void *obj);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_29C550(s32 arg0);
void func_29C820(s32 arg0);
void func_29C7E0(s32 arg0);
void func_29C810(s32 arg0);
void EftShotFx_Update_2494A0(void);
s32 func_003C4480(void);
void func_003C2FB0(void);
void func_003C2D80(void);

#define MENU_S32(off) (*(s32 *)(D_00421CF4 + (off)))
#define MENU_U32(off) (*(u32 *)(D_00421CF4 + (off)))
#define PAD_TRIG (*(u32 *)(D_3B0B00 + 0x144))
#define PAD_PRESS (*(u32 *)(D_3B0B00 + 0x134))

#define M_COLUMN 0x1C8
#define M_ROW 0x1CC
#define M_NAME_LEN 0x1D0
#define M_NAME_BUF 0x1D4
#define M_FLAGS 0x1FC
#define M_PAGE 0x204
#define M_MODE 0x208
#define M_STATE 0x218

/* character currently under the cursor in the name-entry grid */
#define CELL_CHAR() D_00421CA0[MENU_S32(M_PAGE) * 42 + MENU_S32(M_ROW) * 14 + MENU_S32(M_COLUMN)]

/* Menu input handler. mode 0: name entry grid; mode 1: save-slot list. *out is cleared on cancel in name entry. */
void func_003C48F8(s32 *out) {
    u32 flags;
    s32 ch;
    s32 sel;
    u8 *entry;

    if (!func_26EB60(D_00421CF4 + 0x60)) {
        return;
    }
    if (MENU_S32(M_STATE) != 0) {
        return;
    }

    if (MENU_S32(M_MODE) == 0) {
        flags = MENU_U32(M_FLAGS);
        if (flags & 4) {
            if (!(PAD_PRESS & 0x5000)) {
                return;
            }
            MENU_U32(M_FLAGS) = flags & ~4;
            func_297FE0(0, 1, 0x40, 0x40, 1);
            func_26EB78(D_00421CF4 + 0x60, D_00423068);
            return;
        }

        if (PAD_TRIG & 0x10) {
            /* up: previous row with a character */
            do {
                MENU_S32(M_ROW) -= 1;
                if (MENU_S32(M_ROW) < 0) {
                    MENU_S32(M_ROW) = 2;
                }
            } while (CELL_CHAR() == 0);
            func_297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (PAD_TRIG & 0x40) {
            /* down */
            do {
                MENU_S32(M_ROW) += 1;
                if (MENU_S32(M_ROW) >= 3) {
                    MENU_S32(M_ROW) = 0;
                }
            } while (CELL_CHAR() == 0);
            func_297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (PAD_TRIG & 0x80) {
            /* left */
            do {
                MENU_S32(M_COLUMN) -= 1;
                if (MENU_S32(M_COLUMN) < 0) {
                    MENU_S32(M_COLUMN) = 0xD;
                }
            } while (CELL_CHAR() == 0);
            func_297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (PAD_TRIG & 0x20) {
            /* right */
            do {
                MENU_S32(M_COLUMN) += 1;
                if (MENU_S32(M_COLUMN) >= 0xE) {
                    MENU_S32(M_COLUMN) = 0;
                }
            } while (CELL_CHAR() == 0);
            func_297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (PAD_TRIG & 0x400) {
            /* move the name cursor left */
            if (MENU_S32(M_NAME_LEN) <= 0) {
                return;
            }
            MENU_S32(M_NAME_LEN) -= 1;
            func_297FE0(0, 2, 0x40, 0x40, 1);
            return;
        }
        if (PAD_TRIG & 0x800) {
            /* move the name cursor right */
            MENU_S32(M_NAME_LEN) += 1;
            if (MENU_S32(M_NAME_LEN) >= 0x24) {
                MENU_S32(M_NAME_LEN) = 0x23;
                return;
            }
            func_297FE0(0, 2, 0x40, 0x40, 1);
            return;
        }

        if (PAD_PRESS & 0x2000) {
            /* switch character page */
            if (MENU_S32(M_PAGE) != 0) {
                MENU_S32(M_PAGE) = 0;
            } else {
                MENU_S32(M_PAGE) = 1;
            }
            func_297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (PAD_PRESS & 8) {
            /* jump to the end key */
            if (MENU_S32(M_COLUMN) == 0xD && MENU_S32(M_ROW) == 2) {
                return;
            }
            func_297FE0(0, 0, 0x40, 0x40, 1);
            MENU_S32(M_COLUMN) = 0xD;
            MENU_S32(M_ROW) = 2;
            return;
        }
        if (PAD_TRIG & 0x4000) {
            /* confirm */
            ch = CELL_CHAR();
            if (ch == 1) {
                if (!(PAD_PRESS & 0x4000)) {
                    return;
                }
                MENU_U32(M_FLAGS) |= 1;
                sel = func_003C4480();
                if (sel > 0) {
                    func_003C2FB0();
                    func_243A80(0, 0, 0);
                    MENU_S32(0x20C) = ch;
                    func_26EB78(D_00421CF4 + 0x60, D_00423078);
                    func_297FE0(2, 1, 0x40, 0x40, 1);
                    MENU_S32(0x210) = 5;
                    return;
                }
                MENU_U32(M_FLAGS) |= 4;
                func_26EB78(D_00421CF4 + 0x60, D_00423088);
                func_297FE0(2, 2, 0x40, 0x40, 1);
                if (sel >= 0) {
                    MENU_S32(0x210) = 6;
                } else {
                    MENU_S32(0x210) = 7;
                }
                func_2493C0(MENU_S32(0xC), 0x33E9, 0x3802, 0, MENU_S32(0x210));
                return;
            }
            if (ch == 2) {
                /* backspace */
                s32 len = MENU_S32(M_NAME_LEN);

                if (*(s8 *)(D_00421CF4 + M_NAME_BUF + len) != 0) {
                    D_00421CF4[M_NAME_BUF + len] = 0;
                    func_297FE0(0, 2, 0x40, 0x40, 1);
                    len = MENU_S32(M_NAME_LEN);
                    if (len > 0) {
                        MENU_S32(M_NAME_LEN) = len - 1;
                    }
                    return;
                }
                if (len > 0) {
                    MENU_S32(M_NAME_LEN) = len - 1;
                    func_297FE0(0, 2, 0x40, 0x40, 1);
                }
                D_00421CF4[M_NAME_BUF + MENU_S32(M_NAME_LEN)] = 0;
                return;
            }
            /* ordinary character: append to the name */
            {
                s32 len = MENU_S32(M_NAME_LEN);

                if (!(*(s8 *)(D_00421CF4 + M_NAME_BUF + len) == ch && len >= 0x23)) {
                    func_297FE0(2, 0, 0x40, 0x40, 1);
                }
                D_00421CF4[M_NAME_BUF + MENU_S32(M_NAME_LEN)] = (u8)CELL_CHAR();
                MENU_S32(M_NAME_LEN) += 1;
                if (MENU_S32(M_NAME_LEN) < 0x24) {
                    return;
                }
                MENU_S32(M_NAME_LEN) = 0x23;
                MENU_S32(M_COLUMN) = 0xD;
                MENU_S32(M_ROW) = 2;
                return;
            }
        }
        if (PAD_PRESS & 0x1000) {
            /* cancel */
            func_243A80(0, 0, 0);
            *out = 0;
            MENU_U32(M_FLAGS) |= 2;
            func_297FE0(0, 2, 0x40, 0x40, 1);
        }
        return;
    }

    if (MENU_S32(M_MODE) != 1) {
        return;
    }

    /* mode 1: slot list */
    flags = MENU_U32(M_FLAGS);
    if (!(flags & 8)) {
        if (!(PAD_PRESS & 0x4000)) {
            return;
        }
        MENU_U32(M_FLAGS) = flags | 8;
        func_26EB78(D_00421CF4 + 0x60, D_00423098);
        func_297FE0(0, 1, 0x40, 0x40, 1);
        MENU_S32(0x210) = 8;
        func_2493C0(MENU_S32(0xC), 0x33E9, 0x3802, 0, MENU_S32(0x210));
        return;
    }

    if (flags & 0x10) {
        /* confirmation sub-menu (yes / no) */
        if (PAD_TRIG & 0x10) {
            MENU_S32(0x1C4) -= 1;
            if (MENU_S32(0x1C4) < 0) {
                MENU_S32(0x1C4) = 1;
            }
            func_297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (PAD_TRIG & 0x40) {
            MENU_S32(0x1C4) += 1;
            if (MENU_S32(0x1C4) >= 2) {
                MENU_S32(0x1C4) = 0;
            }
            func_297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if ((PAD_PRESS & 0x4000) && MENU_S32(0x1C4) == 0) {
            /* yes: store the current record in the slot */
            entry = D_00387F2C + MENU_S32(0x1BC) * 34;
            __builtin_memcpy(entry + 0x1DDC, D_00421CF4 + 0x640, 32);
            *(s16 *)(entry + 0x1DFC) = *(s16 *)(D_00421CF4 + 0x660);
            func_003C2D80();
            MENU_S32(0x21C) = 0x78;
            MENU_S32(M_STATE) = 10;
            MENU_S32(0x1C4) = 0;
            func_29C550(0);
            func_29C820(1);
            func_29C7E0(1);
            func_29C810(0);
            EftShotFx_Update_2494A0();
            MENU_U32(M_FLAGS) &= ~0x10;
            func_26EB78(D_00421CF4 + 0x88, D_004230B0);
            func_297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        if (!(PAD_PRESS & 0x1000)) {
            if (!(PAD_PRESS & 0x4000)) {
                return;
            }
            if (MENU_S32(0x1C4) != 1) {
                return;
            }
        }
        MENU_U32(M_FLAGS) &= ~0x10;
        func_26EB78(D_00421CF4 + 0x88, D_004230B0);
        func_297FE0(0, 2, 0x40, 0x40, 1);
        MENU_S32(0x210) = 8;
        func_2493C0(MENU_S32(0xC), 0x33E9, 0x3802, 0, MENU_S32(0x210));
        return;
    }

    /* slot browsing: 0x1BC = selected slot, 0x1C0 = first visible slot */
    if ((PAD_TRIG & 0x10) && MENU_S32(0x680) <= 0) {
        MENU_S32(0x1BC) -= 1;
        if (MENU_S32(0x1BC) >= 0) {
            func_297FE0(0, 0, 0x40, 0x40, 1);
        } else {
            MENU_S32(0x1BC) = 0;
        }
        if (MENU_S32(0x1BC) < MENU_S32(0x1C0)) {
            MENU_S32(0x1C0) = MENU_S32(0x1BC);
        }
        MENU_S32(0x680) = 6;
        return;
    }
    if ((PAD_TRIG & 0x40) && MENU_S32(0x680) <= 0) {
        s32 top;

        MENU_S32(0x1BC) += 1;
        if (MENU_S32(0x1BC) >= 0xA) {
            MENU_S32(0x1BC) = 9;
        } else {
            func_297FE0(0, 0, 0x40, 0x40, 1);
        }
        top = MENU_S32(0x1BC) - 2;
        if (MENU_S32(0x1C0) < top) {
            MENU_S32(0x1C0) = top;
        }
        MENU_S32(0x680) = 6;
        return;
    }

    if (PAD_TRIG & 0x480) {
        /* page up */
        if (MENU_S32(0x1C0) > 0) {
            MENU_S32(0x1BC) -= 3;
            MENU_S32(0x1C0) -= 3;
            while (MENU_S32(0x1C0) < 0) {
                MENU_S32(0x1BC) += 1;
                MENU_S32(0x1C0) += 1;
            }
            func_297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (MENU_S32(0x1BC) <= 0) {
            return;
        }
        MENU_S32(0x1BC) = 0;
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }
    if (PAD_TRIG & 0x820) {
        /* page down */
        if (MENU_S32(0x1C0) < 7) {
            MENU_S32(0x1BC) += 3;
            MENU_S32(0x1C0) += 3;
            while (MENU_S32(0x1C0) >= 8) {
                MENU_S32(0x1BC) -= 1;
                MENU_S32(0x1C0) -= 1;
            }
            func_297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (MENU_S32(0x1BC) >= 9) {
            return;
        }
        MENU_S32(0x1BC) = 9;
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }
    if (PAD_TRIG & 0x100) {
        /* top */
        if (MENU_S32(0x1BC) <= 0) {
            return;
        }
        MENU_S32(0x1BC) = 0;
        MENU_S32(0x1C0) = 0;
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }
    if (PAD_TRIG & 0x200) {
        /* bottom */
        if (MENU_S32(0x1BC) >= 9) {
            return;
        }
        MENU_S32(0x1BC) = 9;
        MENU_S32(0x1C0) = 7;
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }

    if (PAD_PRESS & 0x1000) {
        /* back */
        func_243A80(0, 0, 0);
        MENU_U32(M_FLAGS) &= ~8;
        func_297FE0(0, 2, 0x40, 0x40, 1);
        MENU_S32(0x20C) = 0;
        EftShotFx_Update_2494A0();
        return;
    }
    if (!(PAD_PRESS & 0x4000)) {
        return;
    }

    /* select the slot */
    entry = D_00387F2C + MENU_S32(0x1BC) * 34;
    if (*(u16 *)(entry + 0x1DFC) & 1) {
        /* slot in use: ask for confirmation */
        MENU_U32(M_FLAGS) |= 0x10;
        func_297FE0(0, 1, 0x40, 0x40, 1);
        MENU_S32(0x210) = 9;
        func_2493C0(MENU_S32(0xC), 0x33E9, 0x3802, 0, MENU_S32(0x210));
        func_26EAE0(D_00421CF4 + 0x88, 0x3C);
        func_26EA88(D_00421CF4 + 0x88);
        MENU_S32(0x1C4) = 1;
        return;
    }
    /* empty slot: store directly */
    {
        u8 *rec = D_00421CF4;

        __builtin_memcpy(entry + 0x1DDC, rec + 0x640, 32);
        *(s16 *)(entry + 0x1DFC) = *(s16 *)(rec + 0x660);
    }
    func_003C2D80();
    MENU_S32(0x21C) = 0x78;
    MENU_S32(0x1C4) = 0;
    MENU_S32(M_STATE) = 10;
    func_29C550(0);
    func_29C820(1);
    func_29C7E0(1);
    func_29C810(0);
    EftShotFx_Update_2494A0();
    func_297FE0(0, 1, 0x40, 0x40, 1);
}
