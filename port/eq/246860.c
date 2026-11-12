#include "common.h"

extern u8 *D_00387958;
extern u8 *D_00387F2C;
extern u8 *D_003876A4;
extern u8 D_003B0B00[];
extern char D_00374580[], D_00374590[], D_003745A0[], D_00387968[];

extern s32 func_0026EB60(u8 *arg0);
extern void func_0026EB78(u8 *dst, const char *s);
extern void func_0026EAE0(u8 *arg0, s32 arg1);
extern void func_0026EA88(u8 *arg0);
extern void func_00243D18(void);
extern void func_00243BD8(void);
extern void func_00251030(s32 arg0);
extern void func_002984E0(s32 arg0);
extern void func_00298460(s32 arg0, s32 arg1, s32 arg2);
extern void func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_00297FE0(s32 a, s32 b, s32 w, s32 h, s32 flag);

/* Shop screen (buy / sell) state machine. M = *D_00387958:
 *   0x1220 tab (0..3)   0x1F0+4t cursor of tab t   0x200+4t scroll of tab t   0x1210+4t item count of tab t
 *   0x210+4*(256t+cursor) item id (-1 = empty)   0x122C mode flags: 8 list active, 0x10 selling, 0x20 quantity
 *   prompt, 0x40 confirm prompt, 0x80 done   0x1224 quantity   0x1228 confirm choice   0x1288 timer
 *   0x1250 price table (48-byte entries: +0x10 max stock, +0x18 price percent, +0x1C sell value)
 *   inventory I = *D_00387F2C: per item 4 bytes at +0x1F30 (u16 flags, s16 count), money word at +0x283C. */
#define M D_00387958
#define MW(off) (*(s32 *)(M + (off)))
#define PADR (*(u32 *)(D_003B0B00 + 0x144))
#define PADP (*(u32 *)(D_003B0B00 + 0x134))
#define TAB MW(0x1220)
#define CUR MW(0x1F0 + 4 * TAB)
#define SCROLL MW(0x200 + 4 * TAB)
#define COUNT MW(0x1210 + 4 * TAB)
#define ITEM_AT(c) MW(0x210 + 4 * (256 * TAB + (c)))
#define QTY MW(0x1224)
#define MODE MW(0x122C)
#define DONE(b) func_00297FE0(0, (b), 0x40, 0x40, 1)
#define INV_FLAGS(i) (*(u16 *)(D_00387F2C + 4 * (i) + 0x1F30))
#define INV_COUNT(i) (*(s16 *)(D_00387F2C + 4 * (i) + 0x1F32))
#define MONEY (*(u32 *)(D_00387F2C + 0x283C))
#define ENTRY(i) (MW(0x1250) + 48 * (i))
#define EW(i, off) (*(s32 *)(ENTRY(i) + (off)))
#define PRICE(i) (EW(i, 0x18) * MW(0x125C + 8 * MW(0x1284)) / 100)

s32 func_00246860(void)
{
    u32 p;
    u32 pp;
    s32 item;
    s32 maxq;
    s32 i;
    u32 mode;

    if (func_0026EB60(M + 0x28) == 0) {
        return 0;
    }
    mode = MODE;
    if (!(mode & 8)) {
        p = PADR;
        if (p & 0x10) {
            MW(0x1EC) = MW(0x1EC) - 1;
            if (MW(0x1EC) < 0) {
                MW(0x1EC) = 1;
            }
            return DONE(0);
        }
        if (p & 0x40) {
            MW(0x1EC) = MW(0x1EC) + 1;
            if (MW(0x1EC) >= 2) {
                MW(0x1EC) = 0;
            }
            return DONE(0);
        }
        pp = PADP;
        if (pp & 0x4000) {
            if (MW(0x1EC) == 1) {
                MODE = mode | 0x10;
                func_00243D18();
            } else {
                func_00243BD8();
            }
            MODE = MODE | 8;
            for (i = 0; i < 4; i++) {
                MW(0x1F0 + 4 * i) = 0;
                MW(0x200 + 4 * i) = 0;
            }
            TAB = 0;
            func_0026EB78(M + 0x28, D_00374580);
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            MW(0x1288) = 0x32;
            return 0;
        }
        if (pp & 0x1000) {
            MODE = mode & ~8;
            func_0026EB78(M + 0x28, D_00374590);
            func_0026EB78(M + 0x50, D_00374590);
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            MW(0x1288) = 0x1E;
        }
        return 0;
    }

    if (!(mode & 0x20)) {
        /* list navigation */
        p = PADR;
        if (p & 0x10) {
            CUR = CUR - 1;
            if (CUR >= 0) {
                if (CUR < SCROLL) {
                    SCROLL = CUR;
                }
                return DONE(0);
            }
            CUR = 0;
            SCROLL = CUR;
            if (SCROLL < 0) {
                SCROLL = 0;
            }
            return 0;
        }
        if (p & 0x40) {
            CUR = CUR + 1;
            if (CUR < COUNT) {
                if (!(CUR - 4 < SCROLL)) {
                    SCROLL = CUR - 3;
                }
                return DONE(0);
            }
            CUR = CUR - 1;
            return 0;
        }
        if (p & 0xC00) {
            s32 oldcur = CUR;
            s32 oldscr = SCROLL;
            s32 off = oldcur - oldscr;
            if (p & 0x800) {
                s32 last = COUNT - 4;
                if (oldscr < last) {
                    SCROLL = oldscr + 4;
                    if (COUNT - 4 < SCROLL) {
                        SCROLL = COUNT - 4;
                    }
                    DONE(0);
                    CUR = SCROLL + off;
                    return 0;
                }
                if (oldscr != last) {
                    return 0;
                }
                if (oldcur != COUNT - 1) {
                    DONE(0);
                }
                CUR = SCROLL + 3;
                return 0;
            }
            if (oldscr > 0) {
                SCROLL = oldscr - 4;
                if (SCROLL < 0) {
                    SCROLL = 0;
                }
                DONE(0);
                CUR = SCROLL + off;
                return 0;
            }
            if (oldscr != 0) {
                return 0;
            }
            if (oldcur != oldscr) {
                DONE(0);
            }
            CUR = SCROLL;
            return 0;
        }
        if (p & 0x100) {
            if (CUR <= 0) {
                return 0;
            }
            CUR = 0;
            SCROLL = 0;
            return DONE(0);
        }
        if (p & 0x200) {
            s32 last = COUNT - 1;
            if (!(CUR < last)) {
                return 0;
            }
            CUR = last;
            SCROLL = COUNT - 4;
            if (SCROLL < 0) {
                SCROLL = 0;
            }
            return DONE(0);
        }
        if (p & 0x80) {
            TAB = TAB - 1;
            if (TAB < 0) {
                TAB = 3;
            }
            return DONE(0);
        }
        if (p & 0x20) {
            TAB = TAB + 1;
            if (TAB >= 4) {
                TAB = 0;
            }
            return DONE(0);
        }
        pp = PADP;
        if (pp & 0x8000) {
            item = ITEM_AT(CUR);
            if (item == -1) {
                return DONE(7);
            }
            if (INV_FLAGS(item) & 2) {
                INV_FLAGS(item) = INV_FLAGS(item) & 0xFFFD;
            }
            func_00251030(0x3C);
            MW(0x1288) = 0x28;
            return DONE(1);
        }
        if (pp & 0x4000) {
            s32 owned;
            u32 price;
            item = ITEM_AT(CUR);
            owned = INV_COUNT(item);
            if ((MODE & 0x10) || item < 0) {
                if (INV_COUNT(item) <= 0) {
                    return DONE(7);
                }
                MODE = MODE | 0x20;
                DONE(1);
                QTY = 1;
                return 0;
            }
            price = PRICE(item);
            if (!(MONEY < price) && owned < EW(item, 0x10)) {
                MODE = MODE | 0x20;
                DONE(1);
                QTY = 1;
                return 0;
            }
            price = PRICE(item);
            if (MONEY < price) {
                MW(0x1248) = 9;
                func_002493C0(MW(0xAC), 0x36CE, 0x3AE7, 0, MW(0x1248));
            }
            return DONE(7);
        }
        if (pp & 0x1000) {
            MODE = MODE & ~0x18;
            func_0026EB78(M + 0x28, D_003745A0);
            DONE(2);
            MW(0x1288) = 0xA;
        }
        return 0;
    }

    /* quantity prompt (mode 0x20) */
    item = ITEM_AT(CUR);
    if (mode & 0x10) {
        maxq = INV_COUNT(item);
    } else {
        s32 left = EW(item, 0x10) - INV_COUNT(item);
        u32 afford = MONEY / (u32)PRICE(item);
        maxq = left;
        if (!((u32)left < afford)) {
            maxq = (s32)afford;
        }
    }
    mode = MODE;
    if (!(mode & 0x40)) {
        p = PADR;
        if (p & 0x10) {
            QTY = QTY + 1;
            if (maxq < QTY) {
                QTY = maxq;
                return 0;
            }
            return DONE(0);
        }
        if (p & 0x40) {
            QTY = QTY - 1;
            if (QTY > 0) {
                return DONE(0);
            }
            QTY = 1;
            return 0;
        }
        if (p & 0x20) {
            if (QTY != maxq) {
                DONE(0);
            }
            QTY = QTY + 10;
            if (maxq < QTY) {
                QTY = maxq;
            }
            return 0;
        }
        if (p & 0x80) {
            if (QTY != 1) {
                DONE(0);
            }
            QTY = QTY - 10;
            if (QTY <= 0) {
                QTY = 1;
            }
            return 0;
        }
        pp = PADP;
        if (pp & 0x4000) {
            if (QTY <= 0) {
                MODE = mode & ~0x20;
                DONE(2);
                QTY = 0;
                return 0;
            }
            func_0026EAE0(M + 0x78, 0x3C);
            func_0026EA88(M + 0x78);
            MODE = MODE | 0x40;
            MW(0x1228) = 1;
            DONE(1);
            MW(0x1248) = (MODE & 0x10) ? 0xB : 7;
            func_002493C0(MW(0xAC), 0x36CE, 0x3AE7, 0, MW(0x1248));
            return 0;
        }
        if (pp & 0x1000) {
            MODE = mode & ~0x20;
            DONE(2);
            QTY = 0;
        }
        return 0;
    }

    /* confirm prompt (mode 0x40) */
    p = PADR;
    if (p & 0x10) {
        MW(0x1228) = MW(0x1228) + 1;
        if (MW(0x1228) >= 2) {
            MW(0x1228) = 0;
        }
        return DONE(0);
    }
    if (p & 0x40) {
        MW(0x1228) = MW(0x1228) - 1;
        if (MW(0x1228) < 0) {
            MW(0x1228) = 1;
        }
        return DONE(0);
    }
    pp = PADP;
    if (pp & 0x1000) {
        func_0026EB78(M + 0x78, D_00387968);
        MODE = MODE & ~0x40;
        DONE(2);
        MW(0x1288) = 0x3C;
        return 0;
    }
    if (pp & 0x4000) {
        func_0026EB78(M + 0x78, D_00387968);
        MODE = MODE & ~0x60;
        if (MW(0x1228) != 0) {
            DONE(2);
            MW(0x1288) = 0x3C;
            QTY = 0;
            return 0;
        }
        if (MODE & 0x10) {
            u16 *cnt = (u16 *)(D_00387F2C + 4 * item + 0x1F30 + 2);
            *cnt = *cnt - (u16)QTY;
            func_002984E0(QTY * EW(item, 0x1C));
            if (INV_FLAGS(item) & 2) {
                INV_FLAGS(item) = INV_FLAGS(item) & 0xFFFD;
            }
            if (INV_COUNT(item) <= 0) {
                CUR = 0;
                SCROLL = 0;
                INV_COUNT(item) = 0;
            }
            func_00243D18();
        } else {
            u32 price;
            func_00298460(item, EW(item, 0x10), QTY);
            price = PRICE(item);
            MONEY = MONEY - QTY * price;
        }
        MODE = MODE | 0x80;
        MW(0x1288) = 0x3C;
        func_00297FE0((*(s32 *)(D_003876A4 + 0x1C) == 5) ? 2 : 4, 1, 0x40, 0x40, 1);
        QTY = 0;
    }
    return 0;
}
