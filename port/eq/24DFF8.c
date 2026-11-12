#include "common.h"

extern u8 *D_003879A0;
extern u8 *D_003876A4;
extern char D_00374A98[], D_00374AB0[], D_00374AC0[], D_00374AD0[], D_00374AE8[], D_00374BC0[], D_00374BE0[];
extern char D_00374CB8[], D_00374CC8[], D_00375260[], D_00375A70[], D_00375A80[], D_00375A98[], D_00375AB8[];
extern char D_00375AD8[], D_00375AE8[], D_00375B00[], D_00375B18[], D_00375B28[], D_00375B38[], D_00375BC8[];
extern u8 D_00374B00[], D_00374BF8[], D_00374CE0[], D_00374FA0[], D_00375270[], D_00375670[], D_00375B48[];
extern f32 D_00386D70;
extern f32 D_00386D74;

extern void func_00277E70(u8 *dst, s32 val, s64 n);
extern void func_0026EBC0(u8 *ui, const char *name, u8 *out);
extern void func_0026EC48(u8 *ui, u8 *h, s32 *rect);
extern void func_0026EFC8(u8 *ui, u8 *h, s32 flags);
extern void func_0026EEC8(u8 *ui, u8 *h, s32 x, s32 y);
extern void func_0026EC18(u8 *ui, u8 *h, s32 idx);
extern void func_0026EEF8(u8 *ui, u8 *h, f32 f12);
extern void func_0026EF88(u8 *ui, u8 *h, f32 f12);
extern f32 func_0026F148(u8 *ui, u8 *h);
extern void func_0026EC78(u8 *ui, u8 *h, u8 *a2, u8 *a3, s32 *rect, s32 t1, s32 t2, s32 t3);
extern void func_0026EB20(u8 *layer, s32 x, s32 y);
extern void func_0026EA58(u8 *p);
extern void func_00325830(u8 *buf, const void *fmt, s32 n);
extern void func_00249BB8(u8 *ui, u8 *h, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
extern void func_00249DB8(u8 *ui, u8 *h, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
extern void func_0024AB10(u8 *ui, u8 *handles, s32 a2, s32 a3, s32 font, u8 *digits);
extern void func_0024A9D0(u8 *digits, s32 value, s32 count, s32 arg3);
extern void func_0024A198(u8 *ui, u8 *h, s32 a2, s32 a3, s32 t0, s32 id, s32 t2, s32 t3);
extern u8 *func_0024C148(void);

/* Character "edit" screen draw. M = *D_003879A0, S = *D_003876A4. Frame (sp) offsets as in the original:
 * 0x00 handle, 0x10 rect[4], 0x30/0x100 menu name copies, 0xF0 float/handle temp, 0x1C0/0x480 level mark names,
 * 0x1E0 handles, 0x200 mini numbers, 0x600.. handles/digits, 0x740 mini numbers 2, 0x640.. name bufs, 0xB40.. bufs. */
#define M D_003879A0
#define S D_003876A4
#define MW(off) (*(s32 *)(M + (off)))
#define SP(off) (sp + (off))
#define RECT(i) (*(s32 *)(sp + 0x10 + 4 * (i)))
#define SET_RECT(x, y, w, h) do { RECT(0) = (x); RECT(1) = (y); RECT(2) = (w); RECT(3) = (h); } while (0)
#define CELL (7 * MW(0x1CC) + MW(0x1C8))
/* 4-byte slot i of the current record (id u16 at +0, value u16 at +2) */
#define SLOT(c, i) ((c) + 0x1408 + 34 * CELL + 4 * (i))

void func_0024DFF8(void)
{
    u8 sp[0xC60] __attribute__((aligned(16)));
    u8 *ui;
    u8 *c;
    s32 i;
    s32 j;
    s32 v;
    s32 font;

    func_00277E70(*(u8 **)(M + 0xC4), 0, 0x80);
    ui = M + 0x4C;
    if (MW(0x1C4) & 0x40) {
        *(f32 *)(M + 0x322C) = *(f32 *)(M + 0x322C) + D_00386D70;
        if (1.0f <= *(f32 *)(M + 0x322C)) {
            *(f32 *)(M + 0x322C) = 1.0f;
        }
    } else {
        MW(0x322C) = 0;
    }
    func_0026EBC0(ui, D_00374A98, sp);
    func_0026EEF8(ui, sp, *(f32 *)(M + 0x322C));

    if (*(s32 *)(S + 0x1C) == 0x29) {
        v = 0x84;
    } else {
        u8 *tab = (*(s32 *)(S + 0x48C) & 2) ? *(u8 **)(M + 0x1EC) : *(u8 **)(M + 0x1E8);
        v = *(s32 *)(tab + 44 * CELL);
    }
    func_0026EBC0(ui, D_00374AB0, sp);
    func_00249BB8(ui, sp, 0, 0, MW(0x14), v, 2);
    func_0026EBC0(ui, D_00374AC0, sp);
    func_00249DB8(ui, sp, 0, 0, MW(0x18), v, 2);
    func_0026EBC0(ui, D_00374AD0, sp);
    func_0026EFC8(ui, sp, 0x10);
    SET_RECT(0, 32, 256, 64);
    func_0026EBC0(ui, D_00374AE8, sp);
    func_0026EC48(ui, sp, (s32 *)SP(0x10));

    /* main menu entries */
    __builtin_memcpy(SP(0x30), D_00374B00, 192);
    for (i = 0; i < 3;) {
        SET_RECT(0, 32 * i, 256, 32 * i + 32);
        func_0026EBC0(ui, (const char *)SP(0x30 + 64 * i), sp);
        func_0026EC48(ui, sp, (s32 *)SP(0x10));
        if (*(s32 *)(S + 0x1C) == 0x37 && !(i < MW(0x1E0))) {
            func_0026EF88(ui, sp, D_00386D74);
        }
        if (i == MW(0x1D4)) {
            f32 f;
            func_0026EBC0(ui, D_00374BC0, SP(0xF0));
            f = func_0026F148(ui, sp);
            func_0026EEF8(ui, SP(0xF0), f);
        }
        i++;
    }
    func_0026EBC0(ui, D_00374BC0, sp);
    func_0026EEC8(ui, sp, 0, 42 * MW(0x1D4));
    func_0026EC18(ui, sp, 1);
    if (MW(0x3228) == 1 || MW(0x3228) == 7) {
        func_0026EFC8(ui, sp, 1);
    } else {
        func_0026EFC8(ui, sp, 2);
    }
    v = MW(0x1D4);
    SET_RECT(0, v * 32, 256, v * 32 + 32);
    func_0026EBC0(ui, D_00374BE0, sp);
    func_0026EC48(ui, sp, (s32 *)SP(0x10));

    /* logic menu entries */
    __builtin_memcpy(SP(0x100), D_00374BF8, 192);
    for (i = 0; i < 3;) {
        SET_RECT(0, 32 * i, 256, 32 * i + 32);
        func_0026EBC0(ui, (const char *)SP(0x100 + 64 * i), sp);
        func_0026EC48(ui, sp, (s32 *)SP(0x10));
        if (i == MW(0x1D8)) {
            f32 f;
            func_0026EBC0(ui, D_00374CB8, SP(0xF0));
            i++;
            f = func_0026F148(ui, sp);
            func_0026EEF8(ui, SP(0xF0), f);
            func_0026EFC8(ui, sp, 8);
        } else {
            func_0026EFC8(ui, sp, 4);
            i++;
        }
    }
    func_0026EBC0(ui, D_00374CB8, sp);
    func_0026EEC8(ui, sp, 0, 36 * MW(0x1D8));
    v = MW(0x1D8);
    SET_RECT(0, v * 32, 256, v * 32 + 32);
    func_0026EBC0(ui, D_00374CC8, sp);
    func_0026EC48(ui, sp, (s32 *)SP(0x10));

    /* level up marks */
    __builtin_memcpy(SP(0x1C0), D_00374CE0, 704);
    for (i = 0; i < 11; i++) {
        func_0026EBC0(ui, (const char *)SP(0x1C0 + 64 * i), sp);
        if (MW(0x3240 + 4 * i) == 3) {
            func_0026EFC8(ui, sp, 4);
            SET_RECT(0, 0, 32, 32);
            func_0026EC78(ui, sp, M + 4 * i + 0x32AC, M + 4 * i + 0x32D8, (s32 *)SP(0x10), 2, 2, 3);
        } else {
            func_0026EFC8(ui, sp, 8);
        }
    }
    __builtin_memcpy(SP(0x480), D_00374FA0, 704);
    for (i = 0; i < 11; i++) {
        func_0026EBC0(ui, (const char *)SP(0x480 + 64 * i), sp);
        if (MW(0x3240 + 4 * i) == 2) {
            func_0026EFC8(ui, sp, 4);
            SET_RECT(0, 0, 32, 32);
            func_0026EC78(ui, sp, M + 4 * i + 0x32AC, M + 4 * i + 0x32D8, (s32 *)SP(0x10), 2, 2, 3);
        } else {
            func_0026EFC8(ui, sp, 8);
        }
    }
    for (i = 0; i < 3; i++) {
        func_00325830(SP(0x1C0), D_00375260, 2 - i);
        func_0026EBC0(ui, (const char *)SP(0x1C0), SP(0x1E0 + 8 * i));
        if (MW(0x3268) != 0) {
            func_0026EC18(ui, SP(0x1E0 + 8 * i), MW(0x3268) - 1);
        } else {
            func_0026EC18(ui, SP(0x1E0 + 8 * i), 0);
        }
    }
    func_0024A9D0(SP(0xF0), MW(0x323C), 3, 1);
    func_0024AB10(ui, SP(0x1E0), 0, 0, MW(0x335C), SP(0xF0));

    /* mini health numbers */
    __builtin_memcpy(SP(0x200), D_00375270, 1024);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 2; j++) {
            func_0026EBC0(ui, (const char *)SP(0x200 + 128 * i + 64 * j), SP(0x600 + 8 * j));
        }
        func_0024A9D0(SP(0x610), MW(0x326C + 4 * i), 2, 1);
        func_0024AB10(ui, SP(0x600), 0, 0, MW(0x3360), SP(0x610));
    }
    __builtin_memcpy(SP(0x740), D_00375670, 1024);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 2; j++) {
            func_0026EBC0(ui, (const char *)SP(0x740 + 128 * i + 64 * j), SP(0x620 + 8 * j));
            if (MW(0x3240 + 4 * i) != 0) {
                func_0026EC18(ui, SP(0x620 + 8 * j), MW(0x3240 + 4 * i) - 1);
            } else {
                func_0026EC18(ui, SP(0x620 + 8 * j), 0);
            }
        }
        if (MW(0x3240 + 4 * i) == 0) {
            SP(0x630)[0] = 10;
            SP(0x630)[1] = 10;
            SP(0x630)[2] = 0xFF;
            func_0024AB10(ui, SP(0x620), 0, 0, MW(0x3360), SP(0x630));
        } else {
            func_0024A9D0(SP(0x630), MW(0x328C + 4 * i), 2, 1);
            func_0024AB10(ui, SP(0x620), 0, 0, MW(0x3360), SP(0x630));
        }
    }

    /* character select cursor and arrows */
    if (*(s32 *)(S + 0x1C) != 0x37 && *(s32 *)(S + 0x1C) != 0x29) {
        ui = M + 0x74;
        func_0026EB20(ui, 0, 0x18);
        func_0026EBC0(ui, D_00375A70, sp);
        func_0026EEC8(ui, sp, 60 * MW(0x1C8), 0);
        if (MW(0x1C4) & 0x100) {
            func_0026EFC8(ui, sp, 8);
        } else {
            func_0026EFC8(ui, sp, 4);
        }
        func_0026EBC0(ui, D_00375A80, sp);
        func_0026EFC8(ui, sp, 8);
        func_0026EBC0(ui, D_00375A98, sp);
        if (MW(0x3214) < 2 || (MW(0x1C4) & 0x100)) {
            func_0026EFC8(ui, sp, 8);
        } else {
            func_0026EFC8(ui, sp, 4);
        }
        if (!(MW(0x3214) < 2)) {
            SET_RECT(0, 32, 32, 64);
            func_0026EBC0(ui, D_00375AB8, sp);
            func_0026EC48(ui, sp, (s32 *)SP(0x10));
        }
    }
    ui = M + 0x9C;

    func_0026EBC0(ui, D_00375AD8, sp);
    func_0026EEC8(ui, sp, 0, 36 * MW(0x1DC));
    for (i = 0; i < 2; i++) {
        func_0026EBC0(ui, i ? D_00375AE8 : D_00375B00, sp);
        func_0026EEC8(ui, sp, 0, 6);
    }
    for (i = 0; i < 7; i++) {
        func_00325830(SP(0x640), D_00375B18, i + 1);
        func_0026EBC0(ui, (const char *)SP(0x640), sp);
        if (i == MW(0x1DC)) {
            func_0026EC18(ui, sp, 1);
        } else if (i < MW(0x3218)) {
            func_0026EC18(ui, sp, 0);
        } else if (i < MW(0x321C)) {
            func_0026EC18(ui, sp, 3);
        } else {
            func_0026EC18(ui, sp, 2);
        }
    }
    for (i = 0; i < 7; i++) {
        func_00325830(SP(0x680), D_00375B28, i + 1);
        func_0026EBC0(ui, (const char *)SP(0x680), sp);
        func_0026EFC8(ui, sp, 8);
    }
    for (i = 0; i < 7; i++) {
        s32 id;
        func_00325830(SP(0x6A0), D_00375B38, i + 1);
        func_0026EBC0(ui, (const char *)SP(0x6A0), sp);
        c = func_0024C148();
        id = *(s16 *)SLOT(c, i);
        if (id != 0 && i < MW(0x321C)) {
            func_0026EFC8(ui, sp, 4);
            RECT(1) = 0;
            RECT(3) = 64;
            c = func_0024C148();
            id = *(s16 *)SLOT(c, i);
            v = *(s32 *)(MW(0x334C) + 48 * id - 0x28);
            RECT(0) = v << 6;
            RECT(2) = (v << 6) + 64;
            func_0026EC48(ui, sp, (s32 *)SP(0x10));
        } else {
            func_0026EFC8(ui, sp, 8);
        }
    }

    /* small counters */
    __builtin_memcpy(SP(0x6C0), D_00375B48, 128);
    for (i = 0; i < 7; i++) {
        s32 id;
        for (j = 0; j < 4; j++) {
            func_00325830(SP(0xB40 + 32 * j), SP(0x6C0 + 32 * j), i + 1);
            func_0026EBC0(ui, (const char *)SP(0xB40 + 32 * j), SP(0xBC0 + 8 * j));
        }
        c = func_0024C148();
        id = *(s16 *)SLOT(c, i);
        if (id != 0 && i < MW(0x321C)) {
            u8 *ent;
            c = func_0024C148();
            id = *(s16 *)SLOT(c, i);
            ent = (u8 *)(MW(0x334C) + 48 * id);
            if (*(s32 *)(ent - 0x30) & 0x10) {
                SP(0xBE0)[0] = 10;
                c = func_0024C148();
                func_0024A9D0(SP(0xBE1), *(s16 *)(SLOT(c, i) + 2), 3, 1);
                func_0024AB10(ui, SP(0xBC0), -7, 0, MW(0x3360), SP(0xBE0));
                continue;
            }
        }
        SP(0xBE0)[0] = 10;
        SP(0xBE0)[1] = 11;
        SP(0xBE0)[2] = 11;
        SP(0xBE0)[3] = 11;
        SP(0xBE0)[4] = 0xFF;
        font = MW(0x3360);
        func_0024AB10(ui, SP(0xBC0), -7, 0, font, SP(0xBE0));
    }

    /* names */
    for (i = 0; i < 7;) {
        s32 id;
        c = func_0024C148();
        id = *(s16 *)SLOT(c, i);
        i++;
        if (id != 0 && i - 1 < MW(0x321C)) {
            func_00325830(SP(0xBF0), D_00375BC8, i);
            func_0026EBC0(ui, (const char *)SP(0xBF0), sp);
            c = func_0024C148();
            func_0024A198(ui, sp, 2, 0, MW(0x1C), *(s16 *)SLOT(c, i - 1), 0, 0x160);
        }
    }

    for (i = 0; i < 4; i++) {
        s32 t = *(s32 *)(S + 0x1C);
        if ((t == 0x37 || t == 0x29) && i == 2) {
            continue;
        }
        func_0026EA58(M + 40 * i + 0x24);
    }
}
