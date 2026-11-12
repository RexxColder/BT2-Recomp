#include "common.h"

extern u8 *D_00387958;
extern u8 *D_00387F2C;
extern u8 *D_003876A4;
extern char D_00372128[], D_00372138[], D_00372150[], D_00372168[], D_00372180[], D_00372198[], D_003721B0[];
extern char D_00387960[], D_00372AC8[], D_00372AD8[], D_00372AE8[], D_00372AF8[], D_00372F18[], D_00372F38[];
extern char D_003737D0[], D_003737E0[], D_003741F0[], D_00374200[], D_00374518[], D_00374530[], D_00374548[];
extern char D_00374560[], D_00374570[];
extern u8 D_00374218[];
extern f32 D_00386D64;
extern f32 D_00386D68;
extern u8 D_003721C8[], D_003728C8[], D_00372B18[], D_00372F50[], D_00373350[], D_003733D0[], D_003737F0[];
extern u8 D_00373DF0[], D_00373FF0[];

extern void func_00277E70(u8 *dst, s32 val, s64 n);
extern void func_0026EBC0(u8 *ui, const char *name, u8 *out);
extern void func_0026EC48(u8 *ui, u8 *h, s32 *rect);
extern void func_0026EFC8(u8 *ui, u8 *h, s32 flags);
extern void func_0026EEC8(u8 *ui, u8 *h, s32 x, s32 y);
extern void func_0026EC18(u8 *ui, u8 *h, s32 idx);
extern void func_0026EEF8(u8 *ui, u8 *h, f32 f12);
extern f32 func_0026F148(u8 *ui, u8 *h);
extern void func_00249FB8(u8 *ui, u8 *h, s32 a2, s32 a3, s32 font, s32 mood, s32 flag);
extern void func_002495A8(u8 *ui, u8 *h, u8 *ptr, s32 a3);
extern void func_00249778(u8 *ui, u8 *h, u8 *ptr, s32 a3);
extern void func_002498D8(u8 *ui, u8 *h, s32 a2);
extern void func_0024A8A0(u8 *buf, s32 value, s32 n);
extern void func_0024AB10(u8 *ui, u8 *handles, s32 a2, s32 a3, s32 font, u8 *digits);
extern void func_0026EF38(u8 *ui, u8 *h, f32 f12, f32 f13);
extern void func_0026EF88(u8 *ui, u8 *h, f32 f12);
extern void func_0024C060(void);
extern void func_00325830();
extern void func_0026EA58(u8 *p);
extern void func_0024A198(u8 *ui, u8 *h, s32 a2, s32 a3, s32 t0, s32 id, s32 t2, s32 t3);

/* Shop (mc_*) screen draw, part of the item shop: M = *D_00387958, I = *D_00387F2C (inventory).
 * M: 0x1220 tab, 0x1F0+4t cursor, 0x200+4t scroll, 0x1210+4t count, 0x210+4*(256t+i) item id, 0x122C mode flags
 * (0x10 selling, 0x20 quantity prompt, 0x40 confirm, 0x80 done, 0x400 free), 0x1224 quantity, 0x1250 price table
 * (48-byte entries), 0x1284 price index, 0x1248 guide mood.
 * Text blobs are copied to the stack (255 bytes per name) as the original does. Stack (sp) map:
 * 0x00 handle, 0x10 rect[4], 0x30 digits, 0x40 money names, 0x740 handles, 0x780 rect, 0x7A0 name blob 1. */
#define M D_00387958
#define I D_00387F2C
#define MW(off) (*(s32 *)(M + (off)))
#define SP(off) (sp + (off))
#define RECT(i) (*(s32 *)(sp + 0x10 + 4 * (i)))
#define RECT2(i) (*(s32 *)(sp + 0x780 + 4 * (i)))
#define TAB MW(0x1220)
#define CUR MW(0x1F0 + 4 * TAB)
#define SCROLL MW(0x200 + 4 * TAB)
#define COUNT MW(0x1210 + 4 * TAB)
#define ITEM_AT(c) MW(0x210 + 4 * (256 * TAB + (c)))
#define ENT(it) (MW(0x1250) + 48 * (it))
#define EW(it, off) (*(s32 *)(ENT(it) + (off)))
#define PRICE(it) (EW(it, 0x18) * MW(0x125C + 8 * MW(0x1284)) / 100)
#define MONEY (*(u32 *)(I + 0x283C))
#define INV_COUNT(it) (*(s16 *)(I + 4 * (it) + 0x1F32))
#define UI1 (M + 0x28)
#define UI2 (M + 0x50)
#define UI3 (M + 0x78)

void func_00244708(void)
{
    u8 sp[0x1C00] __attribute__((aligned(16)));
    s32 i;
    s32 j;
    s32 mood;
    s32 money;
    s32 it;
    f32 f20;

    func_00277E70(*(u8 **)(M + 0xB0), 0, 0x80);
    func_0026EBC0(UI1, D_00372128, sp);
    if (MW(0x122C) & 0x100) {
        func_00249FB8(UI1, sp, -0x200, 0, MW(0xA8), MW(0x1248), 1);
    } else {
        func_00249FB8(UI1, sp, 0, 0, MW(0xA8), MW(0x1248), 0);
    }
    func_0026EBC0(UI1, D_00372138, sp);
    func_002495A8(UI1, sp, M + 0x1230, 1);
    func_0026EBC0(UI1, D_00372150, sp);
    func_002495A8(UI1, sp, M + 0x1238, 1);
    func_0026EBC0(UI1, D_00372168, sp);
    func_002495A8(UI1, sp, M + 0x1240, 1);
    mood = MW(0x1248);
    if (mood == 0 || mood == 13) {
        func_0026EBC0(UI1, D_00372180, sp);
        func_00249778(UI1, sp, M + 0x1234, 3);
        func_0026EBC0(UI1, D_00372198, sp);
        func_002498D8(UI1, sp, 3);
        func_0026EBC0(UI1, D_003721B0, sp);
        func_002498D8(UI1, sp, 3);
    } else if (mood > 0 && mood < 13) {
        func_0026EBC0(UI1, D_00372180, sp);
        func_002498D8(UI1, sp, 3);
        if (MW(0x122C) & 8) {
            func_0026EBC0(UI1, D_003721B0, sp);
            func_00249778(UI1, sp, M + 0x1244, 3);
        } else {
            func_0026EBC0(UI1, D_00372198, sp);
            func_00249778(UI1, sp, M + 0x123C, 3);
        }
    } else {
        func_0026EBC0(UI1, D_00372180, sp);
        func_002498D8(UI1, sp, 3);
        func_0026EBC0(UI1, D_00372198, sp);
        func_002498D8(UI1, sp, 3);
        func_0026EBC0(UI1, D_003721B0, sp);
        func_002498D8(UI1, sp, 3);
    }

    func_0026EBC0(UI2, D_00387960, sp);
    if (*(s16 *)(I + 0x24EA) > 0) {
        RECT(0) = 0xC0; RECT(1) = 0; RECT(2) = 0x100; RECT(3) = 0x40;
        func_0026EC48(UI2, sp, (s32 *)SP(0x10));
        func_0026EFC8(UI2, sp, 4);
    } else if (*(s16 *)(I + 0x24E6) > 0) {
        RECT(0) = 0x80; RECT(1) = 0; RECT(2) = 0xC0; RECT(3) = 0x40;
        func_0026EC48(UI2, sp, (s32 *)SP(0x10));
        func_0026EFC8(UI2, sp, 4);
    } else if (*(s16 *)(I + 0x24E2) > 0) {
        RECT(0) = 0x40; RECT(1) = 0; RECT(2) = 0x80; RECT(3) = 0x40;
        func_0026EC48(UI2, sp, (s32 *)SP(0x10));
        func_0026EFC8(UI2, sp, 4);
    } else if (*(s16 *)(I + 0x24DE) > 0) {
        RECT(0) = 0; RECT(1) = 0; RECT(2) = 0x40; RECT(3) = 0x40;
        func_0026EC48(UI2, sp, (s32 *)SP(0x10));
        func_0026EFC8(UI2, sp, 4);
    } else {
        func_0026EFC8(UI2, sp, 8);
    }

    /* money */
    __builtin_memcpy(SP(0x40), D_003721C8, 1785);
    it = ITEM_AT(CUR);
    money = MONEY;
    if (MW(0x122C) & 0x20) {
        if (MW(0x122C) & 0x10) {
            money = MW(0x1224) * EW(it, 0x1C) + money;
        } else {
            money = money - MW(0x1224) * PRICE(it);
        }
    }
    if (money > 9999999) {
        money = 9999999;
    }
    for (i = 0; i < 7; i++) {
        func_0026EBC0(UI2, (const char *)SP(0x40 + 255 * i), SP(0x740 + 8 * i));
    }
    func_0024A8A0(SP(0x30), money, 7);
    SP(0x30)[7] = 0xFF;
    func_0024AB10(UI2, SP(0x740), 0, 0, MW(0x127C), SP(0x30));

    /* buy / sell menu */
    __builtin_memcpy(SP(0x7A0), D_003728C8, 510);
    for (i = 0; i < 2; i++) {
        RECT2(0) = 0; RECT2(1) = 32 * i; RECT2(2) = 0x100; RECT2(3) = 32 * i + 32;
        func_0026EBC0(UI1, (const char *)SP(0x7A0 + 255 * i), sp);
        func_0026EC48(UI1, sp, (s32 *)SP(0x780));
        if (MW(0x1EC) == i) {
            func_0026EFC8(UI1, sp, 2);
        }
    }
    RECT2(0) = 0; RECT2(2) = 0x100; RECT2(1) = 32 * MW(0x1EC); RECT2(3) = RECT2(1) + 32;
    func_0026EBC0(UI1, (const char *)SP(0x7A0 + 255 * MW(0x1EC)), sp);
    f20 = func_0026F148(UI1, sp);
    func_0026EBC0(UI1, D_00372AC8, sp);
    func_0026EC48(UI1, sp, (s32 *)SP(0x780));
    func_0026EBC0(UI1, D_00372AD8, sp);
    func_0026EEF8(UI1, sp, f20);
    if (MW(0x1EC) == 0) {
        func_0026EEC8(UI1, sp, 0, 0);
    } else if (MW(0x1EC) == 1) {
        func_0026EEC8(UI1, sp, 15, 45);
    }
    RECT2(0) = 0; RECT2(1) = 32; RECT2(2) = 32; RECT2(3) = 64;
    func_0026EBC0(UI1, D_00372AE8, sp);
    func_0026EC48(UI1, sp, (s32 *)SP(0x780));
    RECT2(1) = 16; RECT2(3) = 32; RECT2(0) = 0; RECT2(2) = 32;
    func_0026EBC0(UI1, D_00372AF8, sp);
    func_0026EC48(UI1, sp, (s32 *)SP(0x780));

    /* item categories */
    __builtin_memcpy(SP(0x9A0), D_00372B18, 1020);
    for (i = 0; i < 4; i++) {
        RECT2(0) = i << 6; RECT2(1) = 0; RECT2(2) = (i << 6) + 64; RECT2(3) = 64;
        func_0026EBC0(UI1, (const char *)SP(0x9A0 + 255 * i), sp);
        func_0026EC48(UI1, sp, (s32 *)SP(0x780));
        if (TAB == i) {
            func_0026EFC8(UI1, sp, 8);
        } else {
            func_0026EFC8(UI1, sp, 4);
        }
    }
    RECT2(3) = 64; RECT2(1) = 0; RECT2(0) = TAB << 6; RECT2(2) = (TAB << 6) + 64;
    func_0026EBC0(UI1, (const char *)SP(0x9A0 + 255 * TAB), sp);
    f20 = func_0026F148(UI1, sp);
    func_0026EBC0(UI1, D_00372F18, sp);
    func_0026EC48(UI1, sp, (s32 *)SP(0x780));
    func_0026EEC8(UI1, sp, 50 * TAB, 0);
    func_0026EEF8(UI1, sp, f20);
    RECT2(2) = 0x100; RECT2(0) = 0; RECT2(1) = 32 * TAB; RECT2(3) = 32 * TAB + 32;
    func_0026EBC0(UI1, D_00372F38, sp);
    func_0026EC48(UI1, sp, (s32 *)SP(0x780));

    /* item list: names and plates */
    __builtin_memcpy(SP(0xDA0), D_00372F50, 1020);
    __builtin_memcpy(SP(0x7A0), D_00373350, 128);
    for (i = 0; i < 4; i++) {
        func_0026EBC0(UI1, (const char *)SP(0xDA0 + 255 * i), sp);
        it = ITEM_AT(SCROLL + i);
        if (it == -1) {
            func_0026EFC8(UI1, sp, 8);
            func_0026EBC0(UI1, (const char *)SP(0x7A0 + 32 * i), sp);
            func_0026EFC8(UI1, sp, 4);
        } else {
            func_0026EFC8(UI1, sp, 4);
            func_0024A198(UI1, sp, 2, 0, MW(0x1254), it + 1, 0, 0x160);
            func_0026EBC0(UI1, (const char *)SP(0x7A0 + 32 * i), sp);
            if (MW(0x122C) & 0x400) {
                func_0026EFC8(UI1, sp, 8);
            } else if (MONEY < (u32)PRICE(it)) {
                func_0026EFC8(UI1, sp, 4);
            } else if (INV_COUNT(it) < EW(it, 0x10)) {
                func_0026EFC8(UI1, sp, 8);
            } else {
                func_0026EFC8(UI1, sp, 4);
            }
        }
    }

    /* potara icons per row */
    __builtin_memcpy(SP(0x11A0), D_003733D0, 1020);
    for (i = 0; i < 4; i++) {
        s32 v;
        it = ITEM_AT(SCROLL + i);
        v = EW(it, 8);
        RECT2(1) = 0; RECT2(3) = 0x40; RECT2(0) = v << 6; RECT2(2) = (v << 6) + 0x40;
        func_0026EBC0(UI1, (const char *)SP(0x11A0 + 255 * i), sp);
        if (it == -1) {
            func_0026EFC8(UI1, sp, 8);
        } else {
            func_0026EFC8(UI1, sp, 4);
            func_0026EC48(UI1, sp, (s32 *)SP(0x780));
        }
    }

    /* scroll arrows */
    func_0026EBC0(UI1, D_003737D0, sp);
    func_0026EEC8(UI1, sp, 0, 36 * (CUR - SCROLL));
    if (COUNT > 0) {
        func_0026EFC8(UI1, sp, 4);
    } else {
        func_0026EFC8(UI1, sp, 8);
    }
    func_0026EBC0(UI1, D_003737E0, sp);
    if (SCROLL > 0) {
        func_0026EFC8(UI1, sp, 4);
    } else {
        func_0026EFC8(UI1, sp, 8);
    }
    func_0026EBC0(UI1, D_00372AE8, sp);
    if (SCROLL + 4 < 0x100 && ITEM_AT(SCROLL + 4) != -1) {
        func_0026EFC8(UI1, sp, 4);
    } else {
        func_0026EFC8(UI1, sp, 8);
    }

    /* item prices (money_number2) */
    __builtin_memcpy(SP(0x15A0), D_003737F0, 1530);
    it = ITEM_AT(CUR);
    j = 0;
    if (it != -1) {
        if (MW(0x122C) & 0x400) {
            j = EW(it, 0x1C);
        } else {
            j = PRICE(it);
        }
    }
    for (i = 0; i < 6; i++) {
        func_0026EBC0(UI1, (const char *)SP(0x15A0 + 255 * i), SP(0x830 + 8 * i));
    }
    func_0024A8A0(SP(0x820), j, 6);
    SP(0x820)[6] = 0xFF;
    func_0024AB10(UI1, SP(0x830), 0, 0, MW(0x127C), SP(0x820));

    /* yes / no */
    __builtin_memcpy(SP(0x7A0), D_00373DF0, 510);
    for (i = 0; i < 2; i++) {
        func_0026EBC0(UI3, (const char *)SP(0x7A0 + 255 * i), sp);
        if (i == MW(0x1228)) {
            func_0026EFC8(UI3, sp, 8);
        } else {
            func_0026EFC8(UI3, sp, 4);
        }
    }
    __builtin_memcpy(SP(0x9C0), D_00373FF0, 510);
    for (i = 0; i < 2; i++) {
        *(s32 *)SP(0x9A0) = 0;
        *(s32 *)SP(0x9A4) = i << 6;
        *(s32 *)SP(0x9A8) = 0x80;
        *(s32 *)SP(0x9AC) = (i << 6) + 0x40;
        func_0026EBC0(UI3, (const char *)SP(0x9C0 + 255 * i), sp);
        func_0026EC48(UI3, sp, (s32 *)SP(0x9A0));
        if (i == MW(0x1228)) {
            func_0026EFC8(UI3, sp, 8);
        } else {
            func_0026EFC8(UI3, sp, 4);
        }
    }
    *(s32 *)SP(0xBC0) = 0;
    *(s32 *)SP(0xBC8) = 0x80;
    *(s32 *)SP(0xBC4) = MW(0x1228) << 6;
    *(s32 *)SP(0xBCC) = (MW(0x1228) << 6) + 0x40;
    func_0026EBC0(UI3, D_003741F0, sp);
    func_0026EC48(UI3, sp, (s32 *)SP(0xBC0));
    func_0026EBC0(UI3, D_00374200, sp);
    if (MW(0x122C) & 0x40) {
        func_0026EFC8(UI3, sp, 4);
        func_0026EEC8(UI3, sp, 0, 65 * MW(0x1228));
    } else {
        func_0026EFC8(UI3, sp, 8);
    }

    /* quantity */
    __builtin_memcpy(SP(0xBF0), D_00374218, 765);
    mood = MW(0x1224);
    *(s32 *)SP(0xBE0) = 0;
    for (i = 0; i < 3; i++) {
        func_0026EBC0(UI1, (const char *)SP(0xBF0 + 255 * i), SP(0xEF0 + 8 * i));
        func_0026EC48(UI1, SP(0xEF0 + 8 * i), (s32 *)MW(0x1278));
    }
    func_0024A8A0(SP(0xBE0), mood, 3);
    SP(0xBE0)[3] = 0xFF;
    func_0024AB10(UI1, SP(0xEF0), 0, 0, MW(0x1278), SP(0xBE0));
    for (i = 0; i < 3; i++) {
        func_0026EFC8(UI1, SP(0xEF0 + 8 * i), 4);
    }

    if (MW(0x122C) & 0x20) {
        s32 maxq;
        it = ITEM_AT(CUR);
        if (MW(0x122C) & 0x10) {
            maxq = INV_COUNT(it);
        } else {
            maxq = EW(it, 0x10) - INV_COUNT(it);
        }
        func_0026EBC0(UI1, D_00372AF8, sp);
        if (MW(0x1224) < 2) {
            func_0026EFC8(UI1, sp, 8);
        } else {
            func_0026EFC8(UI1, sp, 4);
        }
        func_0026EBC0(UI1, D_00374518, sp);
        if (MW(0x1224) < maxq && ((MW(0x122C) & 0x10) || !(MONEY < (u32)((MW(0x1224) + 1) * PRICE(it))))) {
            func_0026EFC8(UI1, sp, 4);
        } else {
            func_0026EFC8(UI1, sp, 8);
        }
    } else {
        func_0026EBC0(UI1, D_00374518, sp);
        func_0026EFC8(UI1, sp, 8);
        func_0026EBC0(UI1, D_00372AF8, sp);
        func_0026EFC8(UI1, sp, 8);
    }

    /* owned counts */
    if (MW(0x122C) & 0x400) {
        for (i = 0; i < 4;) {
            it = ITEM_AT(SCROLL + i);
            j = INV_COUNT(it);
            for (mood = 0; mood < 3; mood++) {
                func_00325830(SP(0xF40 + 255 * mood), D_00374530, i + 1, 3 - mood);
                func_0026EBC0(UI1, (const char *)SP(0xF40 + 255 * mood), SP(0xF20 + 8 * mood));
                func_0026EC48(UI1, SP(0xF20 + 8 * mood), (s32 *)MW(0x1280));
            }
            func_0024A8A0(SP(0xF10), j, 3);
            SP(0xF10)[3] = 0xFF;
            func_0024AB10(UI1, SP(0xF20), 0, 0, MW(0x1280), SP(0xF10));
            if (it == -1) {
                for (mood = 0; mood < 3; mood++) {
                    func_0026EFC8(UI1, SP(0xF20 + 8 * mood), 8);
                }
            } else {
                for (mood = 0; mood < 3; mood++) {
                    func_0026EFC8(UI1, SP(0xF20 + 8 * mood), 4);
                }
            }
            i++;
        }
        for (i = 0; i < 4;) {
            func_00325830(SP(0x1240), D_00374548, i + 1);
            it = ITEM_AT(SCROLL + i);
            i++;
            func_0026EBC0(UI1, (const char *)SP(0x1240), sp);
            func_0026EC48(UI1, sp, (s32 *)(MW(0x1280) + 0xDC));
            if (it == -1) {
                func_0026EFC8(UI1, sp, 8);
            } else {
                func_0026EFC8(UI1, sp, 4);
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            for (mood = 0; mood < 3; mood++) {
                func_00325830(SP(0x1360 + 255 * mood), D_00374530, i + 1, 3 - mood);
                func_0026EBC0(UI1, (const char *)SP(0x1360 + 255 * mood), SP(0x1340 + 8 * mood));
                func_0026EFC8(UI1, SP(0x1340 + 8 * mood), 8);
            }
            func_00325830(SP(0x1360), D_00374548, i + 1);
            func_0026EBC0(UI1, (const char *)SP(0x1360), SP(0x1340));
            func_0026EFC8(UI1, SP(0x1340), 8);
        }
    }

    /* scroll bar */
    j = 0;
    if (ITEM_AT(0) != -1) {
        j = 1;
        while (j < 0x100 && ITEM_AT(j) != -1) {
            j++;
        }
    }
    mood = (j < 4) ? 4 : j;
    f20 = (4.0f / (f32)mood) * D_00386D68;
    {
        f32 fp = ((f32)SCROLL * D_00386D64) / (f32)mood;
        u32 pos = (u32)fp;
        func_0026EBC0(UI1, D_00374560, sp);
        func_0026EF38(UI1, sp, 1.0f, f20);
        func_0026EEC8(UI1, sp, 0, (s32)pos);
    }
    if (mood == 4) {
        func_0026EF88(UI1, sp, 0.5f);
    } else {
        func_0026EF88(UI1, sp, 1.0f);
    }
    *(s32 *)SP(0x1660) = 0;
    *(s32 *)SP(0x1664) = (MW(0x122C) & 0x200) ? 0x20 : 0;
    *(s32 *)SP(0x1668) = 0x200;
    *(s32 *)SP(0x166C) = *(s32 *)SP(0x1664) + 0x20;
    func_0026EBC0(UI1, D_00374570, sp);
    func_0026EC48(UI1, sp, (s32 *)SP(0x1660));
    if (MW(0x122C) & 0x20) {
        MW(0x1BC) = 0;
    } else {
        MW(0x1BC) = *(s32 *)(MW(0xC4) + 0x10);
    }
    for (i = 0; i < 4; i++) {
        if (i == 3) {
            continue;
        }
        if (i == 2) {
            func_0024C060();
        }
        func_0026EA58(M + 40 * i);
    }
}
