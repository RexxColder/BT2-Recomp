#include "common.h"

/* 0x003D9098: item-collection ("potara") menu screen refresh. G = *D_004263E8 is the menu block:
 * G+0x14 item records (0x30 bytes: +8 icon, +0x10 quantity), G+0x18 text bank, G+0x1C layer 0 (28), G+0x44 layer 1 (68),
 * G+0x154 pad flags, G+0x158 current category (0..3), G+0x15C+4*cat cursor, G+0x16C+4*cat scroll, G+0x17C+0x1B24*cat+12*k
 * slot k of the category (+0 item id or -1, +8 count), G+0x6E0C+4*cat slot count, G+0x6E24/0x6E28/0x6E2C selected items,
 * G+0x6E30 yes/no cursor. D_00387F2C + 0x1F30 + 4*item = u16 item flags (bit0 known, bit1 new). Returns the stale v0
 * of the last call (result of func_26EA58). */
extern u8 *D_004263E8 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

extern char D_00426458[]; /* mc_textwindow */
extern char D_00426468[]; /* mc_Guide_mouth */
extern char D_00426478[]; /* mc_collect_number%d */
extern char D_00426490[]; /* mc_dummy_text_1 */
extern char D_004264A0[]; /* mc_potara_1 */
extern char D_004264B0[]; /* mc_potara_1_big */
extern char D_004264C0[]; /* mc_dummy_text_2 */
extern char D_004264D0[]; /* mc_potara_2 */
extern char D_004264E0[]; /* mc_potara_2_big */
extern char D_004264F0[]; /* 4 x 255 bytes: mc_item_category_icon_* names */
extern char D_004268F0[]; /* mc_item_category_icon_on */
extern char D_00426910[]; /* mc_item_category_name */
extern char D_00426928[]; /* mc_potara_%d */
extern char D_00426938[]; /* mc_dummy_text_%d */
extern char D_00426950[]; /* mc_mini_numer_%d_x */
extern char D_00426968[]; /* mc_mini_numer_%d_%d */
extern char D_00426980[]; /* mc_item_plate%d */
extern char D_00426990[]; /* mc_new%d */
extern char D_004269A0[]; /* mc_cursor */
extern char D_004269B0[]; /* mc_yazirusi_down */
extern char D_004269C8[]; /* mc_yazirusi_up */
extern char D_004269D8[]; /* mc_plate_ber */
extern char D_004269E8[]; /* mc_item_name */
extern char D_004269F8[]; /* mc_potara_3 */
extern char D_00426A08[]; /* mc_light1 */
extern char D_00426A18[]; /* mc_button_icon */
extern char D_00426A28[]; /* 2 x 255 bytes: mc_yesno_plate_* names */
extern char D_00426C28[]; /* 2 x 255 bytes: mc_yesno_off_* names */
extern char D_00426E28[]; /* mc_yesno_on */
extern char D_00426E38[]; /* mc_yesno_on_cursor */

extern s32 func_277E70();
extern s32 func_26EBC0();
extern s32 func_249FB8();
extern s32 func_249778();
extern s32 func_325830();
extern s32 func_26EC48();
extern s32 func_24A8A0();
extern s32 func_26EFC8();
extern s32 func_24A598();
extern s32 func_26EC18();
extern s32 func_26EEC8();
extern s32 func_26EA58();
extern f32 func_26F148();
extern void func_26EEF8(u8 *layer, u8 *h, s32 a2, s32 a3, f32 scale);
extern s32 func_26EF38(u8 *layer, u8 *h, s32 a2, s32 a3, f32 a, f32 b);
extern void Font_PrintFitted(u8 *layer, u8 *h, s32 a2, s32 a3, u8 *bank, s32 id, s32 flag, s32 width);
extern void Num_DrawDigits(u8 *layer, u8 *refs, s32 x, s32 y, u8 *cells, u8 *digits);

#define G D_004263E8
#define ITEM(i) (*(u8 **)(G + 0x14) + 0x30 * (i))
#define SLOT(cat, k) (G + 0x17C + (cat) * 0x1B24 + 12 * (k))
#define CAT (*(s32 *)(G + 0x158))
#define CURSOR(cat) (*(s32 *)(G + 0x15C + 4 * (cat)))
#define SCROLL(cat) (*(s32 *)(G + 0x16C + 4 * (cat)))
#define COUNT(cat) (*(s32 *)(G + 0x6E0C + 4 * (cat)))
#define FLAGS(item) (*(u16 *)(D_00387F2C + 0x1F30 + 4 * (item)))
#define TEXT_BANK (*(u8 **)(G + 0x18))
#define SHOW 4
#define HIDE 8

struct Frame {
    u8 handle[16];       /* 0x00 */
    s32 rect[4];         /* 0x10 */
    u8 pad_20[16];
    u8 digits[16];       /* 0x30 */
    u8 numRefs[32];      /* 0x40: 4 handles of 8 bytes */
    char nameBuf[256];   /* 0x60 */
    char catNames[1024]; /* 0x160 */
    char potaraBuf[256]; /* 0x560 */
    char dummyBuf[256];  /* 0x660 */
    char miniXBuf[256];  /* 0x760 */
    char plateBuf[256];  /* 0x860 */
    char newBuf[256];    /* 0x960 */
    u8 digits2[16];      /* 0xA60 */
    char miniNames[780]; /* 0xA70: 3 x 255 */
    u8 miniRefs[32];     /* 0xD70 */
    char yesPlate[512];  /* 0xD90 */
    char yesOff[512];    /* 0xF90 */
};

#define SET_RECT(x0, y0, x1, y1) \
    do { \
        f.rect[0] = (x0); \
        f.rect[1] = (y0); \
        f.rect[2] = (x1); \
        f.rect[3] = (y1); \
    } while (0)

/* text slot of a known item: its name, or the "???" string when the item is not yet known */
#define SHOW_ITEM_TEXT(layer, item) \
    do { \
        func_26EFC8((layer), f.handle, SHOW); \
        if (FLAGS(item) & 1) { \
            Font_PrintFitted((layer), f.handle, 2, 0, TEXT_BANK, (item) + 1, 0, 0x160); \
        } else { \
            func_24A598((layer), f.handle, 2, 0, TEXT_BANK, 0x244, 0); \
        } \
    } while (0)

s32 func_003D9098(void) {
    struct Frame f;
    u8 *L;
    f32 catScale = 1.0f;
    s32 i;
    s32 j;
    s32 sel;
    s32 item;
    s32 cur;
    s32 cnt;
    s32 icon;
    u32 barY;
    f32 barPos;
    f32 barScale;
    s32 res;

    func_277E70(*(u8 **)(G + 0x6C), 0, 0x80);
    L = G + 0x1C;
    func_26EBC0(L, D_00426458, f.handle);
    func_249FB8(L, f.handle, 0, 0, *(u8 **)(G + 8), *(s32 *)(G + 0x6E38), 2);
    func_26EBC0(L, D_00426468, f.handle);
    func_249778(L, f.handle, G + 0x6E34, 1);

    /* four "collect number" digit cells */
    for (i = 0; i < 4; i++) {
        func_325830(f.nameBuf, D_00426478, 4 - i);
        func_26EBC0(L, f.nameBuf, f.numRefs + 8 * i);
        func_26EC48(L, f.numRefs + 8 * i, *(s32 *)(G + 0x6E48));
    }
    func_24A8A0(f.digits, *(s16 *)(D_00387F2C + 0x2356), 4);
    f.digits[4] = 0xFF;
    f.digits[0] = 11;
    Num_DrawDigits(L, f.numRefs, 0, 0, *(u8 **)(G + 0x6E48), f.digits);
    for (i = 0; i < 4; i++) {
        func_26EFC8(L, f.numRefs + 8 * i, SHOW);
    }

    /* two selected items (potara 1 and 2) */
    sel = *(s32 *)(G + 0x6E24);
    func_26EBC0(L, D_00426490, f.handle);
    if (sel == -1) {
        func_26EFC8(L, f.handle, HIDE);
    } else {
        SHOW_ITEM_TEXT(L, sel);
    }
    func_26EBC0(L, D_004264A0, f.handle);
    if (sel == -1) {
        func_26EFC8(L, f.handle, HIDE);
    } else {
        icon = *(s32 *)(ITEM(sel) + 8);
        SET_RECT(icon << 6, 0, (icon << 6) + 64, 64);
        func_26EFC8(L, f.handle, SHOW);
        func_26EC48(L, f.handle, f.rect);
    }
    icon = *(s32 *)(ITEM(sel) + 8);
    SET_RECT(icon << 7, 0, (icon << 7) + 128, 128);
    func_26EBC0(L, D_004264B0, f.handle);
    func_26EC48(L, f.handle, f.rect);

    sel = *(s32 *)(G + 0x6E28);
    func_26EBC0(L, D_004264C0, f.handle);
    if (sel == -1) {
        func_26EFC8(L, f.handle, HIDE);
    } else {
        SHOW_ITEM_TEXT(L, sel);
    }
    func_26EBC0(L, D_004264D0, f.handle);
    if (sel == -1) {
        func_26EFC8(L, f.handle, HIDE);
    } else {
        icon = *(s32 *)(ITEM(sel) + 8);
        SET_RECT(icon << 6, 0, (icon << 6) + 64, 64);
        func_26EFC8(L, f.handle, SHOW);
        func_26EC48(L, f.handle, f.rect);
    }
    icon = *(s32 *)(ITEM(sel) + 8);
    SET_RECT(icon << 7, 0, (icon << 7) + 128, 128);
    func_26EBC0(L, D_004264E0, f.handle);
    func_26EC48(L, f.handle, f.rect);

    /* category tabs */
    __builtin_memcpy(f.catNames, D_004264F0, 1020);
    for (i = 0; i < 4; i++) {
        func_26EBC0(L, f.catNames + 255 * i, f.handle);
        if (CAT == i) {
            catScale = func_26F148(L, f.handle);
            func_26EFC8(L, f.handle, HIDE);
        } else {
            SET_RECT(i << 6, 0, (i << 6) + 64, 64);
            func_26EFC8(L, f.handle, SHOW);
            func_26EC48(L, f.handle, f.rect);
        }
    }
    SET_RECT(CAT << 6, 0, (CAT << 6) + 64, 64);
    func_26EBC0(L, D_004268F0, f.handle);
    func_26EC48(L, f.handle, f.rect);
    func_26EEC8(L, f.handle, 50 * CAT, 0);
    func_26EEF8(L, f.handle, 0, 0, catScale);
    SET_RECT(0, 32 * CAT, 256, 32 * CAT + 32);
    func_26EBC0(L, D_00426910, f.handle);
    func_26EC48(L, f.handle, f.rect);

    /* the four visible rows of the current category */
    for (i = 0; i < 4; i++) {
        item = *(s32 *)SLOT(CAT, SCROLL(CAT) + i);
        func_325830(f.potaraBuf, D_00426928, i + 4);
        func_26EBC0(L, f.potaraBuf, f.handle);
        if (*(s32 *)SLOT(CAT, SCROLL(CAT) + i) == -1) {
            func_26EFC8(L, f.handle, HIDE);
        } else {
            icon = *(s32 *)(ITEM(item) + 8);
            SET_RECT(icon << 6, 0, (icon << 6) + 64, 64);
            func_26EFC8(L, f.handle, SHOW);
            func_26EC48(L, f.handle, f.rect);
        }

        func_325830(f.dummyBuf, D_00426938, i + 4);
        func_26EBC0(L, f.dummyBuf, f.handle);
        if (*(s32 *)SLOT(CAT, SCROLL(CAT) + i) == -1) {
            func_26EFC8(L, f.handle, HIDE);
        } else {
            SHOW_ITEM_TEXT(L, item);
        }

        /* quantity badge */
        func_325830(f.miniXBuf, D_00426950, i + 4);
        func_26EBC0(L, f.miniXBuf, f.handle);
        cur = *(s32 *)SLOT(CAT, SCROLL(CAT) + i);
        if (cur != -1 && *(s32 *)(ITEM(cur) + 0x10) >= 2 && (FLAGS(item) & 1)) {
            SET_RECT(48, 32, 64, 64);
            func_26EC48(L, f.handle, f.rect);
            func_26EFC8(L, f.handle, SHOW);
        } else {
            func_26EFC8(L, f.handle, HIDE);
        }

        /* quantity digits */
        cnt = *(s32 *)(SLOT(CAT, SCROLL(CAT) + i) + 8);
        for (j = 0; j < 3; j++) {
            func_325830(f.miniNames + 255 * j, D_00426968, i + 4, 3 - j);
            func_26EBC0(L, f.miniNames + 255 * j, f.miniRefs + 8 * j);
        }
        func_24A8A0(f.digits2, cnt, 3);
        f.digits2[3] = 0xFF;
        for (j = 0; j < 3; j++) {
            func_26EC48(L, f.miniRefs + 8 * j, *(s32 *)(G + 0x6E44));
        }
        Num_DrawDigits(L, f.miniRefs, 0, 0, *(u8 **)(G + 0x6E44), f.digits2);
        cur = *(s32 *)SLOT(CAT, SCROLL(CAT) + i);
        if (cur != -1 && *(s32 *)(ITEM(cur) + 0x10) >= 2 && (FLAGS(item) & 1)) {
            for (j = 0; j < 3; j++) {
                func_26EFC8(L, f.miniRefs + 8 * j, SHOW);
            }
        } else {
            for (j = 0; j < 3; j++) {
                func_26EFC8(L, f.miniRefs + 8 * j, HIDE);
            }
        }

        /* row plate: highlighted when under the cursor */
        func_325830(f.plateBuf, D_00426980, i + 4);
        func_26EBC0(L, f.plateBuf, f.handle);
        if (CURSOR(CAT) - SCROLL(CAT) == i) {
            func_26EC18(L, f.handle, 1);
        } else if (FLAGS(item) & 1) {
            func_26EC18(L, f.handle, 0);
        } else {
            func_26EC18(L, f.handle, 2);
        }

        /* "new" mark */
        func_325830(f.newBuf, D_00426990, i + 4);
        func_26EBC0(L, f.newBuf, f.handle);
        cur = *(s32 *)SLOT(CAT, SCROLL(CAT) + i);
        if (cur != -1 && (FLAGS(cur) & 2)) {
            SET_RECT(0, 32, 64, 64);
            func_26EC48(L, f.handle, f.rect);
            func_26EFC8(L, f.handle, SHOW);
        } else {
            func_26EFC8(L, f.handle, HIDE);
        }
    }

    /* cursor, scroll arrows, scroll bar */
    func_26EBC0(L, D_004269A0, f.handle);
    func_26EEC8(L, f.handle, 0, 36 * (CURSOR(CAT) - SCROLL(CAT)));
    SET_RECT(0, 32, 32, 64);
    func_26EBC0(L, D_004269B0, f.handle);
    func_26EC48(L, f.handle, f.rect);
    if (SCROLL(CAT) + 4 < COUNT(CAT)) {
        func_26EFC8(L, f.handle, SHOW);
    } else {
        func_26EFC8(L, f.handle, HIDE);
    }
    func_26EBC0(L, D_004269C8, f.handle);
    if (SCROLL(CAT) > 0) {
        func_26EFC8(L, f.handle, SHOW);
    } else {
        func_26EFC8(L, f.handle, HIDE);
    }
    cnt = COUNT(CAT);
    if (cnt < 4) {
        cnt = 4;
    }
    barPos = (f32)SCROLL(CAT) * 144.0f / (f32)cnt;
    barScale = (4.0f / (f32)cnt) * 4.5f;
    barY = (u32)barPos;
    func_26EBC0(L, D_004269D8, f.handle);
    func_26EF38(L, f.handle, 0, 0, 1.0f, barScale);
    func_26EEC8(L, f.handle, 0, barY);

    /* detail panel for the selected item */
    sel = *(s32 *)(G + 0x6E2C);
    func_26EBC0(L, D_004269E8, f.handle);
    if (sel == -1) {
        func_26EFC8(L, f.handle, HIDE);
    } else {
        func_26EFC8(L, f.handle, SHOW);
        Font_PrintFitted(L, f.handle, 2, 0, TEXT_BANK, sel + 1, 1, 0x160);
    }
    func_26EBC0(L, D_004269F8, f.handle);
    if (sel == -1) {
        func_26EFC8(L, f.handle, HIDE);
    } else {
        icon = *(s32 *)(ITEM(sel) + 8);
        SET_RECT(icon << 7, 0, (icon << 7) + 128, 128);
        func_26EFC8(L, f.handle, SHOW);
        func_26EC48(L, f.handle, f.rect);
    }
    func_26EBC0(L, D_00426A08, f.handle);
    func_26EFC8(L, f.handle, 0x80);
    {
        s32 y = 32;
        if (*(s32 *)(G + 0x154) & 0x80) {
            y = 0;
        }
        SET_RECT(0, y, 0x200, y + 32);
    }
    func_26EBC0(L, D_00426A18, f.handle);
    func_26EC48(L, f.handle, f.rect);

    /* yes/no box on layer 1 */
    L = G + 0x44;
    __builtin_memcpy(f.yesPlate, D_00426A28, 510);
    for (i = 0; i < 2; i++) {
        func_26EBC0(L, f.yesPlate + 255 * i, f.handle);
        if (i == *(s32 *)(G + 0x6E30)) {
            func_26EFC8(L, f.handle, HIDE);
        } else {
            func_26EFC8(L, f.handle, SHOW);
        }
    }
    __builtin_memcpy(f.yesOff, D_00426C28, 510);
    for (i = 0; i < 2; i++) {
        SET_RECT(0, i << 6, 0x80, (i << 6) + 64);
        func_26EBC0(L, f.yesOff + 255 * i, f.handle);
        func_26EC48(L, f.handle, f.rect);
        if (i == *(s32 *)(G + 0x6E30)) {
            func_26EFC8(L, f.handle, HIDE);
        } else {
            func_26EFC8(L, f.handle, SHOW);
        }
    }
    SET_RECT(0, *(s32 *)(G + 0x6E30) << 6, 0x80, (*(s32 *)(G + 0x6E30) << 6) + 64);
    func_26EBC0(L, D_00426E28, f.handle);
    func_26EC48(L, f.handle, f.rect);
    func_26EBC0(L, D_00426E38, f.handle);
    if ((*(s32 *)(G + 0x154) & 0xC) == 4) {
        func_26EFC8(L, f.handle, SHOW);
        func_26EEC8(L, f.handle, 0, 48 * *(s32 *)(G + 0x6E30));
    } else {
        func_26EFC8(L, f.handle, HIDE);
    }

    for (i = 0; i < 2; i++) {
        res = func_26EA58(G + 0x1C + 40 * i);
    }
    return res;
}
