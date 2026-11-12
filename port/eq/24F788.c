#include "common.h"

extern u8 *D_003879A0;
extern u8 *D_003876A4;
extern u8 D_003B0B00[];
extern char D_00374A88[], D_00375BE0[], D_00375BF0[], D_00375C00[], D_00375C10[], D_00375C20[], D_003879A8[];

extern s32 func_0026EB60(u8 *arg0);
extern void func_0026EB78(u8 *dst, const char *s);
extern void func_0026EAE0(u8 *arg0, s32 arg1);
extern void func_0026EA88(u8 *arg0);
extern void func_0024CF40(void);
extern s32 func_0024AD60(u8 *table, s32 *pos, s32 row);
extern s32 func_0024ACE8(u8 *table, s32 *pos, s32 row);
extern void func_0024AEA0(u8 *table, s32 *col, s32 *row, s32 cols);
extern void func_0024ADE8(u8 *table, s32 *col, s32 *row, s32 cols);
extern void func_0024CD30(s32 arg0);
extern void func_0024F558();
extern void func_0024F768();
extern void func_00248640();
extern void func_002484D8(s32 arg0, s32 arg1);
extern void func_00248690(void);
extern void func_00251030(s32 arg0);
extern void func_00251088(void);
extern void func_0024C380(s32 arg0);
extern void func_0024C528();
extern void func_0024C7A8();
extern u8 *func_0024C148(void);
extern s32 func_00297FE0(s32 a, s32 b, s32 w, s32 h, s32 flag);

/* Per-frame update of the "edit / logic" menu. M = *D_003879A0, state M[0x3228] in 0..11.
 * col M[0x1C8], row M[0x1CC] select a 34-byte record in the record table (func_0024C148() + 0x1408);
 * M[0x1DC] picks a 4-byte slot (u16 id, u16 value) in it. */
#define M D_003879A0
#define S D_003876A4
#define MW(off) (*(s32 *)(M + (off)))
#define CELL (7 * MW(0x1CC) + MW(0x1C8))
#define REC(c) ((c) + 0x1408 + 34 * CELL)
#define SLOTID(c) (*(s16 *)(REC(c) + 4 * MW(0x1DC)))
#define PAD_R (*(u32 *)(D_003B0B00 + 0x144))
#define PAD_P (*(u32 *)(D_003B0B00 + 0x134))
#define PAD_A (*(u32 *)(D_003B0B00 + ((*(s32 *)(S + 0x48C) & 1) ? 0x2C0 : 0x140) + 4))
#define PAD_B (*(u32 *)(D_003B0B00 + ((*(s32 *)(S + 0x48C) & 1) ? 0x2B0 : 0x130) + 4))
#define DN(a, b) func_00297FE0((a), (b), 0x40, 0x40, 1)

/* paste the current record's 28 bytes into the scratch record at M+0x3314 and clear the chosen slot */
static void copy_record(void)
{
    u8 *c = func_0024C148();
    __builtin_memcpy(M + 0x3314, REC(c), 28);
    *(u16 *)(M + 4 * MW(0x1DC) + 0x3314) = 0;
    *(u16 *)(M + 4 * MW(0x1DC) + 0x3316) = 0;
}

s32 func_0024F788(s32 *out)
{
    u8 *c;
    u32 p;
    s32 id;

    if (func_0026EB60(M + 0x4C) == 0) {
        return 0;
    }
    if ((u32)MW(0x3228) >= 12) {
        return 0;
    }
    switch (MW(0x3228)) {
    case 0:
        p = PAD_R;
        if (p & 0x80) {
            func_0024CF40();
            func_0024AD60(*(u8 **)(M + 0x1E8), (s32 *)(M + 0x1C8), MW(0x1CC));
            func_0024F558(0);
            return DN(0, 8);
        }
        if (p & 0x20) {
            func_0024CF40();
            func_0024ACE8(*(u8 **)(M + 0x1E8), (s32 *)(M + 0x1C8), MW(0x1CC));
            func_0024F558(0);
            return DN(0, 8);
        }
        if (p & 0x10) {
            func_0024CF40();
            func_0024AEA0(*(u8 **)(M + 0x1E8), (s32 *)(M + 0x1C8), (s32 *)(M + 0x1CC), MW(0x3214));
            func_0024CD30(0);
            func_0026EB78(M + 0x74, D_00375BE0);
            func_0024F558();
            return DN(1, 2);
        }
        if (p & 0x40) {
            func_0024CF40();
            func_0024ADE8(*(u8 **)(M + 0x1E8), (s32 *)(M + 0x1C8), (s32 *)(M + 0x1CC), MW(0x3214));
            func_0024CD30(0);
            func_0026EB78(M + 0x74, D_00375BF0);
            func_0024F558();
            return DN(1, 2);
        }
        p = PAD_P;
        if (p & 0x4000) {
            func_0026EB78(M + 0x4C, D_00374A88);
            func_0026EB78(M + 0x74, D_003879A8);
            MW(0x3228) = 1;
            return DN(0, 1);
        }
        if (p & 0x1000) {
            if (MW(0x3224) != 4) {
                return 0;
            }
            *out = 0;
            func_0024F768();
            return DN(0, 2);
        }
        return 0;

    case 1:
        p = PAD_A;
        if (p & 0x10) {
            if (MW(0x1E0) < 2) {
                return 0;
            }
            MW(0x1D4) = MW(0x1D4) - 1;
            if (MW(0x1D4) < 0) {
                MW(0x1D4) = MW(0x1E0) - 1;
            }
            return DN(0, 0);
        }
        if (p & 0x40) {
            if (MW(0x1E0) < 2) {
                return 0;
            }
            MW(0x1D4) = MW(0x1D4) + 1;
            if (MW(0x1E0) - 1 < MW(0x1D4)) {
                MW(0x1D4) = 0;
            }
            return DN(0, 0);
        }
        p = PAD_B;
        if (p & 0x4000) {
            switch (MW(0x1D4)) {
            case 1:
                func_0026EB78(M + 0x4C, D_00375C00);
                c = func_0024C148();
                MW(0x1D8) = *(s16 *)(c + 34 * CELL + 0x1426);
                MW(0x3228) = 2;
                return DN(0, 1);
            case 0:
                func_0026EAE0(M + 0x9C, 0x3C);
                func_0026EA88(M + 0x9C);
                MW(0x1DC) = 0;
                MW(0x3228) = 3;
                return DN(0, 1);
            case 2:
                if (*(s32 *)(S + 0x1C) == 0x37) {
                    return DN(0, 1);
                }
                func_00248640();
                func_002484D8(CELL, *(s32 *)(*(u8 **)(M + 0x1E8) + 44 * CELL));
                MW(0x3228) = 4;
                return DN(0, 1);
            default:
                return DN(0, 1);
            }
        }
        if (p & 0x1000) {
            if (*(s32 *)(S + 0x1C) == 0x37) {
                if (!(MW(0x1C4) & 0x40)) {
                    return 0;
                }
                *out = 0;
                func_0024F768();
                return DN(0, 2);
            }
            func_0026EB78(M + 0x4C, D_00375C10);
            func_0026EAE0(M + 0x74, 0x3C);
            func_0026EA88(M + 0x74);
            MW(0x3228) = 0;
            return DN(0, 2);
        }
        return 0;

    case 2:
        p = PAD_A;
        if (p & 0x10) {
            MW(0x1D8) = MW(0x1D8) - 1;
            if (MW(0x1D8) < 0) {
                MW(0x1D8) = 2;
            }
            return DN(0, 0);
        }
        if (p & 0x40) {
            MW(0x1D8) = MW(0x1D8) + 1;
            if (!(MW(0x1D8) < 3)) {
                MW(0x1D8) = 0;
            }
            return DN(0, 0);
        }
        p = PAD_B;
        if (p & 0x4000) {
            func_0026EB78(M + 0x4C, D_00375C20);
            c = func_0024C148();
            *(u16 *)(c + 34 * CELL + 0x1426) = (u16)MW(0x1D8);
            MW(0x3228) = 1;
            return DN(0, 1);
        }
        if (p & 0x1000) {
            func_0026EB78(M + 0x4C, D_00375C20);
            c = func_0024C148();
            MW(0x1D8) = *(s16 *)(c + 34 * CELL + 0x1426);
            MW(0x3228) = 1;
            return DN(0, 2);
        }
        return 0;

    case 3:
        p = PAD_A;
        if (p & 0x10) {
            MW(0x1DC) = MW(0x1DC) - 1;
            if (MW(0x1DC) < 0) {
                MW(0x1DC) = MW(0x321C) - 1;
            }
            return DN(0, 0);
        }
        if (p & 0x40) {
            MW(0x1DC) = MW(0x1DC) + 1;
            if (MW(0x321C) - 1 < MW(0x1DC)) {
                MW(0x1DC) = 0;
            }
            return DN(0, 0);
        }
        p = PAD_B;
        if (p & 0x2000) {
            c = func_0024C148();
            if (SLOTID(c) == 0) {
                return DN(0, 7);
            }
            copy_record();
            func_0024C380(1);
            if (MW(0x3220) < MW(0x321C)) {
                MW(0x3304) = 1;
                MW(0x3310) = 3;
            } else {
                c = func_0024C148();
                id = SLOTID(c);
                if (*(s32 *)(*(u8 **)(M + 0x334C) + 48 * id - 0x30) & 0x10) {
                    MW(0x3304) = 1;
                    MW(0x3310) = 1;
                } else {
                    func_0024C528();
                    func_0024F558();
                }
            }
            return DN(0, 1);
        }
        if (p & 0x8000) {
            c = func_0024C148();
            if (SLOTID(c) == 0) {
                return DN(0, 7);
            }
            func_00251030(0x3C);
            MW(0x3228) = 5;
            return DN(0, 1);
        }
        if (p & 0x4000) {
            MW(0x1C4) |= 0x100;
            MW(0x1C4) |= 0x400;
            MW(0x3230) = 0xF;
            return DN(0, 1);
        }
        if (p & 0x1000) {
            func_0026EB78(M + 0x9C, D_003879A8);
            MW(0x3228) = 1;
            return DN(0, 2);
        }
        return 0;

    case 4:
        if (PAD_B & 0x5000) {
            func_00248690();
            MW(0x3228) = 1;
            return DN(0, 2);
        }
        return 0;

    case 5:
        if (PAD_B & 0x9000) {
            func_00251088();
            MW(0x3228) = 3;
            return DN(0, 2);
        }
        return 0;

    case 6:
        p = PAD_B;
        if (p & 0x4000) {
            c = func_0024C148();
            if (SLOTID(c) != 0) {
                if (MW(0x3220) < MW(0x321C)) {
                    MW(0x3304) = 5;
                    MW(0x3310) = 4;
                } else {
                    c = func_0024C148();
                    id = SLOTID(c);
                    if (*(s32 *)(*(u8 **)(M + 0x334C) + 48 * id - 0x30) & 0x10) {
                        MW(0x3304) = 5;
                        MW(0x3310) = 2;
                    } else {
                        func_0024C7A8();
                        MW(0x3228) = 3;
                    }
                }
            } else {
                func_0024C7A8();
                MW(0x3228) = 3;
            }
            func_0026EAE0(M + 0x9C, 0x3C);
            func_0026EA88(M + 0x9C);
            return DN(0, 1);
        }
        if (p & 0x1000) {
            MW(0x1C4) |= 0x100;
            MW(0x1C4) |= 0x400;
            MW(0x3230) = 0xF;
            *(s32 *)(S + 0x48C) |= 0x10;
            return DN(0, 2);
        }
        return 0;

    case 7:
        p = PAD_R;
        if (p & 0x10) {
            MW(0x1D4) = MW(0x1D4) - 1;
            if (MW(0x1D4) < 0) {
                MW(0x1D4) = MW(0x1E0) - 1;
            }
            return DN(0, 0);
        }
        if (p & 0x40) {
            MW(0x1D4) = MW(0x1D4) + 1;
            if (MW(0x1E0) - 1 < MW(0x1D4)) {
                MW(0x1D4) = 0;
            }
            return DN(0, 0);
        }
        p = PAD_P;
        if (p & 0x4000) {
            switch (MW(0x1D4)) {
            case 1:
                func_0026EB78(M + 0x4C, D_00375C00);
                c = func_0024C148();
                MW(0x1D8) = *(s16 *)(c + 34 * CELL + 0x1426);
                MW(0x3228) = 9;
                return DN(0, 1);
            case 0:
                func_0026EAE0(M + 0x9C, 0x3C);
                func_0026EA88(M + 0x9C);
                MW(0x1DC) = 0;
                MW(0x3228) = 8;
                return DN(0, 1);
            case 2:
                func_00248640();
                func_002484D8(CELL, *(s32 *)(*(u8 **)(M + 0x1E8) + 44 * CELL));
                MW(0x3228) = 10;
                return DN(0, 1);
            default:
                return DN(0, 1);
            }
        }
        if (p & 0x1000) {
            if (!(MW(0x1C4) & 0x40)) {
                return 0;
            }
            *out = 0;
            func_0024F768();
            return DN(0, 2);
        }
        return 0;

    case 8:
        p = PAD_R;
        if (p & 0x10) {
            MW(0x1DC) = MW(0x1DC) - 1;
            if (MW(0x1DC) < 0) {
                MW(0x1DC) = MW(0x321C) - 1;
            }
            return DN(0, 0);
        }
        if (p & 0x40) {
            MW(0x1DC) = MW(0x1DC) + 1;
            if (MW(0x321C) - 1 < MW(0x1DC)) {
                MW(0x1DC) = 0;
            }
            return DN(0, 0);
        }
        p = PAD_P;
        if (p & 0x8000) {
            c = func_0024C148();
            if (SLOTID(c) == 0) {
                return DN(0, 7);
            }
            func_00251030(0x3C);
            MW(0x3228) = 11;
            return DN(0, 1);
        }
        if (p & 0x5000) {
            func_0026EB78(M + 0x9C, D_003879A8);
            MW(0x3228) = 7;
            return DN(0, 2);
        }
        return 0;

    case 9:
        if (PAD_P & 0x5000) {
            func_0026EB78(M + 0x4C, D_00375C20);
            MW(0x3228) = 7;
            return DN(0, 2);
        }
        return 0;

    case 10:
        if (PAD_P & 0x5000) {
            func_00248690();
            MW(0x3228) = 7;
            return DN(0, 2);
        }
        return 0;

    default: /* 11 */
        if (PAD_P & 0x9000) {
            func_00251088();
            MW(0x3228) = 8;
            return DN(0, 2);
        }
        return 0;
    }
}
