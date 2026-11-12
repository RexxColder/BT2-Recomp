#include "common.h"

extern u8 *D_003879C0;
extern u8 *D_003876A4;
extern char D_00375D28[], D_00375E78[], D_00375E98[], D_00375EB8[], D_00375ED0[], D_00375EE8[], D_00375EF8[];
extern char D_00375F10[], D_00375F28[], D_00375F38[], D_00375F50[], D_00375F60[], D_00375FF0[], D_00376000[];
extern char D_00376010[], D_00376020[], D_003879C8[];
extern u8 D_00375D38[];
extern u8 D_00375F70[];
extern f32 D_00386D78;
extern f32 D_00386D7C;

extern void func_00277E70(u8 *dst, s32 val, s64 n);
extern void func_0026EBC0(u8 *ui, const char *name, u8 *out);
extern void func_0026EC48(u8 *ui, u8 *h, s32 *rect);
extern void func_0026EFC8(u8 *ui, u8 *h, s32 flags);
extern void func_0026EEC8(u8 *ui, u8 *h, s32 x, s32 y);
extern void func_0026EC18(u8 *ui, u8 *h, s32 idx);
extern void func_0026EF38(u8 *ui, u8 *h, f32 f12, f32 f13);
extern void func_0026EA58(u8 *p);
extern void func_00325830(u8 *buf, const void *fmt, s32 n);
extern void func_0024AB10(u8 *ui, u8 *handles, s32 a2, s32 a3, s32 font, u8 *digits);
extern void func_0024A9D0(u8 *digits, s32 value, s32 count, s32 arg3);
extern void func_0024A198(u8 *ui, u8 *h, s32 a2, s32 a3, s32 t0, s32 id, s32 t2, s32 t3);
extern u8 *func_0024C148(void);
extern s32 func_0024B4F0(s32 arg0, s32 arg1, s32 arg2);

/* "Collection" (mc_*) screen draw. M = *D_003879C0 (screen state), S = *D_003876A4 (settings, S[0x1C]==0x38 is the
 * shop variant). Frame layout (sp): 0x00 handle, 0x10 rect[4], 0x30 icon names, 0x170 name buf, 0x190 handles[4],
 * 0x1B0 digits, 0x1C0/0x200/0x240/0x260 name bufs, 0x280 mini-number formats, 0x300 name bufs, 0x380 handles[4]. */
#define M D_003879C0
#define S D_003876A4
#define MW(off) (*(s32 *)(M + (off)))
#define IDX MW(0xC4)
#define SHOP (*(s32 *)(S + 0x1C) == 0x38)
#define BASE(i) (MW(0x2E34 + 4 * IDX) + (i))
/* item id of list entry i (shop screens use the 0xF4 table, the others 0xF8) */
#define ITEM(i) MW(0x90C * IDX + 4 * BASE(i) + (SHOP ? 0xF4 : 0xF8))
#define ITEM_F4(i) MW(0x90C * IDX + 4 * BASE(i) + 0xF4)
#define ITEM_F8(i) MW(0x90C * IDX + 4 * BASE(i) + 0xF8)
#define FL(c, it) (*(u16 *)((c) + 4 * (it) + 0x1F30))
#define REC(c) ((c) + 0x1408 + 34 * *(s32 *)(S + 0x494) + 4 * *(s32 *)(S + 0x498))
#define SP(off) (sp + (off))
#define RECT(i) (*(s32 *)(sp + 0x10 + 4 * (i)))

void func_002518F0(void)
{
    u8 sp[0x3A0] __attribute__((aligned(16)));
    u8 *obj;
    u8 *ui;
    s32 i;
    s32 k;
    s32 q;
    s32 r;
    u8 *c;
    f32 f20;
    s32 s0;

    func_00277E70(*(u8 **)(M + 0x5C), 0, 0x80);
    obj = M + 0xC;
    if (!SHOP) {
        RECT(1) = 64;
        RECT(3) = 128;
        RECT(2) = 512;
        RECT(0) = 0;
        func_0026EBC0(obj, D_00375D28, sp);
        func_0026EC48(obj, sp, (s32 *)SP(0x10));
    }
    __builtin_memcpy(SP(0x30), D_00375D38, 320);
    for (i = 0; i < 5; i++) {
        func_0026EBC0(obj, (const char *)SP(0x30 + 64 * i), sp);
        if (SHOP && !(i < MW(0xC8))) {
            func_0026EFC8(obj, sp, 8);
        }
        q = i / 4;
        r = i - 4 * q;
        RECT(1) = q << 6;
        RECT(3) = (q << 6) + 64;
        RECT(2) = (r << 6) + 64;
        RECT(0) = r << 6;
        func_0026EC48(obj, sp, (s32 *)SP(0x10));
    }
    func_0026EBC0(obj, D_00375E78, sp);
    func_0026EEC8(obj, sp, 50 * IDX, 0);
    q = IDX / 4;
    RECT(1) = q << 6;
    RECT(3) = RECT(1) + 64;
    r = IDX - 4 * (IDX / 4);
    RECT(0) = r << 6;
    RECT(2) = RECT(0) + 64;
    func_0026EBC0(obj, D_00375E98, sp);
    func_0026EC48(obj, sp, (s32 *)SP(0x10));
    RECT(2) = 256;
    RECT(1) = IDX * 32;
    RECT(3) = IDX * 32 + 32;
    RECT(0) = 0;
    func_0026EBC0(obj, D_00375EB8, sp);
    func_0026EC48(obj, sp, (s32 *)SP(0x10));
    for (k = 0; k < 4; k++) {
        func_00325830(SP(0x170), D_00375ED0, 4 - k);
        func_0026EBC0(obj, (const char *)SP(0x170), SP(0x190 + 8 * k));
    }
    if (SHOP) {
        SP(0x1B0)[0] = 10;
        SP(0x1B0)[1] = 10;
        SP(0x1B0)[2] = 10;
        SP(0x1B0)[3] = 10;
        SP(0x1B0)[4] = 0xFF;
    } else {
        func_0024A9D0(SP(0x1B0), MW(0xDC), 3, 1);
        SP(0x1B0)[3] = 11;
        SP(0x1B0)[4] = 0xFF;
    }
    func_0024AB10(obj, SP(0x190), 0, 0, MW(0x2E60), SP(0x1B0));

    ui = M + 0x34;
    for (i = 0; SHOP ? i < 6 : i < 7; i++) {
        if (BASE(i) == MW(0xB0 + 4 * IDX)) {
            MW(0xCC) = i + (SHOP ? 1 : 0);
            break;
        }
    }
    func_0026EBC0(ui, D_00375EE8, sp);
    func_0026EEC8(ui, sp, 0, 36 * MW(0xCC));
    for (k = 0; k < 2; k++) {
        func_0026EBC0(ui, k ? D_00375EF8 : D_00375F10, sp);
        func_0026EEC8(ui, sp, 0, 6);
    }

    /* item plates */
    for (i = 0; i < 7; i++) {
        s32 it;
        func_00325830(SP(0x1C0), D_00375F28, i + 1);
        func_0026EBC0(ui, (const char *)SP(0x1C0), sp);
        if (SHOP && i == 0) {
            func_0026EC18(ui, sp, 4);
            continue;
        }
        if (i == MW(0xCC)) {
            func_0026EC18(ui, sp, 1);
            continue;
        }
        c = func_0024C148();
        it = ITEM(i);
        if (!(FL(c, it) & 1)) {
            func_0026EC18(ui, sp, 2);
        } else if (SHOP) {
            if (func_0024B4F0(ITEM_F4(i), *(s32 *)(S + 0x4B0), MW(0x2E5C)) == 0) {
                func_0026EC18(ui, sp, 2);
            } else {
                func_0026EC18(ui, sp, 0);
            }
        } else {
            func_0026EC18(ui, sp, 0);
        }
    }

    /* names */
    for (i = 0; i < 7; i++) {
        s32 id;
        func_00325830(SP(0x200), D_00375F38, i + 1);
        func_0026EBC0(ui, (const char *)SP(0x200), sp);
        if (SHOP && i == 0) {
            c = func_0024C148();
            if (*(s16 *)REC(c) == 0) {
                continue;
            }
            c = func_0024C148();
            id = *(s16 *)REC(c) - 1;
        } else {
            c = func_0024C148();
            id = 579;
            {
                s32 it = SHOP ? ITEM_F4(i) : ITEM_F8(i);
                if (FL(c, it) & 1) {
                    id = it;
                }
            }
        }
        func_0024A198(ui, sp, 2, 0, MW(8), id + 1, 0, 0x160);
    }

    /* potara icons */
    for (i = 0; i < 7; i++) {
        s32 a2;
        func_00325830(SP(0x240), D_00375F50, i + 1);
        func_0026EBC0(ui, (const char *)SP(0x240), sp);
        a2 = IDX;
        if (SHOP && i == 0) {
            c = func_0024C148();
            a2 = *(s32 *)(MW(0x2E5C) + 48 * *(s16 *)REC(c) - 0x28);
        }
        if (a2 == 4) {
            s32 x = i + 4;
            q = x / 4;
            r = x - 4 * q;
        } else {
            q = a2 / 4;
            r = a2 - 4 * q;
        }
        RECT(1) = q << 6;
        RECT(3) = (q << 6) + 64;
        RECT(0) = r << 6;
        RECT(2) = (r << 6) + 64;
        func_0026EC48(ui, sp, (s32 *)SP(0x10));
    }

    /* "new" markers */
    for (i = 0; i < 7; i++) {
        s32 it;
        func_00325830(SP(0x260), D_00375F60, i + 1);
        func_0026EBC0(ui, (const char *)SP(0x260), sp);
        RECT(1) = 32;
        RECT(3) = 64;
        RECT(0) = 0;
        RECT(2) = 64;
        if (SHOP && i == 0) {
            func_0026EFC8(ui, sp, 8);
            continue;
        }
        c = func_0024C148();
        it = SHOP ? ITEM_F4(i) : ITEM_F8(i);
        if (!(FL(c, it) & 1)) {
            func_0026EFC8(ui, sp, 8);
            continue;
        }
        c = func_0024C148();
        it = SHOP ? ITEM_F4(i) : ITEM_F8(i);
        if (FL(c, it) & 2) {
            func_0026EFC8(ui, sp, 4);
            func_0026EC48(ui, sp, (s32 *)SP(0x10));
        } else {
            func_0026EFC8(ui, sp, 8);
        }
    }

    /* small counters */
    __builtin_memcpy(SP(0x280), D_00375F70, 128);
    for (i = 0; i < 7; i++) {
        s32 font;
        for (k = 0; k < 4; k++) {
            func_00325830(SP(0x300 + 32 * k), SP(0x280 + 32 * k), i + 1);
            func_0026EBC0(ui, (const char *)SP(0x300 + 32 * k), SP(0x380 + 8 * k));
        }
        if (SHOP && i == 0) {
            u8 *ent;
            c = func_0024C148();
            ent = (u8 *)(MW(0x2E5C) + 48 * *(s16 *)REC(c));
            if (*(s32 *)(ent - 0x30) & 0x10) {
                SP(0x1B0)[0] = 10;
                c = func_0024C148();
                func_0024A9D0(SP(0x1B1), *(s16 *)(REC(c) + 2), 3, 1);
            } else {
                SP(0x1B0)[0] = 10;
                SP(0x1B0)[3] = 11;
                SP(0x1B0)[1] = 11;
                SP(0x1B0)[2] = 11;
                SP(0x1B0)[4] = 0xFF;
            }
            func_0024AB10(ui, SP(0x380), -7, 0, MW(0x2E64), SP(0x1B0));
        } else {
            s32 it;
            c = func_0024C148();
            it = SHOP ? ITEM_F4(i) : ITEM_F8(i);
            if ((FL(c, it) & 1) && *(s32 *)(MW(0x2E5C) + 48 * it + 0x10) != 1) {
                SP(0x1B0)[0] = 12;
                c = func_0024C148();
                func_0024A9D0(SP(0x1B1), *(s16 *)((c) + 4 * (SHOP ? ITEM_F4(i) : ITEM_F8(i)) + 0x1F32), 3, 1);
            } else {
                SP(0x1B0)[0] = 10;
                SP(0x1B0)[1] = 10;
                SP(0x1B0)[2] = 10;
                SP(0x1B0)[3] = 10;
                SP(0x1B0)[4] = 0xFF;
            }
            font = MW(0x2E64);
            func_0024AB10(ui, SP(0x380), 0, 0, font, SP(0x1B0));
        }
    }

    /* scroll bar and arrows */
    if (!SHOP) {
        func_0026EBC0(ui, D_003879C8, sp);
        func_0026EFC8(ui, sp, 8);
    }
    f20 = ((SHOP ? 6.0f : 7.0f) / (f32)MW(0xE4 + 4 * IDX)) * D_00386D78;
    s0 = (s32)((D_00386D7C / (f32)MW(0xE4 + 4 * IDX)) * (f32)MW(0x2E34 + 4 * IDX));
    func_0026EBC0(ui, D_00375FF0, sp);
    func_0026EF38(ui, sp, 1.0f, f20);
    func_0026EEC8(ui, sp, 0, s0);
    if (SHOP) {
        func_0026EBC0(ui, D_00376000, sp);
        func_0026EFC8(ui, sp, 8);
        func_0026EBC0(ui, D_00376010, sp);
        func_0026EFC8(ui, sp, 4);
    } else {
        func_0026EBC0(ui, D_00376010, sp);
        func_0026EFC8(ui, sp, 8);
        func_0026EBC0(ui, D_00376000, sp);
        func_0026EFC8(ui, sp, 4);
    }
    if (MW(0x2E34 + 4 * IDX) == 0) {
        func_0026EFC8(ui, sp, 8);
    }
    RECT(3) = 64;
    RECT(2) = 32;
    RECT(1) = 32;
    RECT(0) = 0;
    func_0026EBC0(ui, D_00376020, sp);
    func_0026EC48(ui, sp, (s32 *)SP(0x10));
    func_0026EFC8(ui, sp, 4);
    if (MW(0x2E48 + 4 * IDX) == MW(0xE4 + 4 * IDX) - 1) {
        func_0026EFC8(ui, sp, 8);
    }
    for (i = 0; i < 2; i++) {
        func_0026EA58(M + 40 * i + 0xC);
    }
}
