#include "common.h"

/* Menu overlay: loads the character-select / battle UI resource (a package of offset tables), relocates
 * every table and fills the object's pointer slots. obj[0] = raw buffer, obj[4] = package header. */

extern u8 *D_003876A4;

s32 func_00100D58(s32 arg0, s32 arg1, s32 arg2);
u8 *func_002B24C8(u8 *arg0, u8 *arg1, s32 *arg2);
void Res_RelocateOffsets(u8 **table, u8 *arg1, u8 *arg2);
void func_0026E7F0(u8 *dst, u8 *src, u8 *arg2);
void func_0026EAE0(u8 *obj, s32 arg1);
void func_0026EB78(u8 *obj, const char *name);

#define W(p, off) (*(s32 *)((p) + (off)))
#define P(p, off) (*(u8 **)((p) + (off)))
#define SEC(h, off) ((h) + (W(h, off) & ~3))
#define MODE_A (*(s32 *)(D_003876A4 + 0x8C))
#define MODE_B (*(s32 *)(D_003876A4 + 0x90))
#define FLAGS (*(u32 *)(D_003876A4 + 0x18))

u8 *func_003D5360(u8 *obj) {
    u8 *hdr;
    u8 *tbl = NULL;
    u8 *src;
    s32 idx[2];
    s32 slot;
    s32 slot2;
    s32 base_off;
    s32 i;
    s32 a;
    s32 b;
    s32 m;

    if (P(obj, 0) == NULL) {
        func_00100D58(W(D_003876A4, 4) + W(D_003876A4, 0x8C) + 4, 0, 1);
        do {
            P(obj, 0) = (u8 *)func_00100D58(0, 0, 0);
        } while (P(obj, 0) == NULL);
    }
    P(obj, 4) = func_002B24C8(P(obj, 0), NULL, NULL);
    hdr = P(obj, 4);

    m = MODE_A;
    if (m >= 0 && m <= 2) {
        P(obj, 0x170) = SEC(hdr, 0x1C);
    }
    Res_RelocateOffsets((u8 **)(obj + 0x170), P(obj, 0x170), P(obj, 0x170));

    slot = 0;
    m = MODE_A;
    if (m >= 0 && m <= 2) {
        slot = 2;
        tbl = SEC(P(obj, 4), 0x58);
    }
    Res_RelocateOffsets(&tbl, tbl, tbl);
    W(obj, 0x17C + 4 * slot) = W(tbl, 0x10);
    W(obj, 0x17C) = W(tbl, 0x10) + 0x40;

    slot = 0;
    slot2 = 0;
    m = MODE_A;
    if (m == 0 || m == 1 || m == 2) {
        slot = 1;
        if (m == 0) {
            slot2 = 1;
        }
        tbl = SEC(P(obj, 4), 0x5C);
    }
    Res_RelocateOffsets(&tbl, tbl, tbl);
    if ((FLAGS & 0x10) == 0) {
        W(obj, 0x17C + 4 * slot) = W(tbl, 0x10);
    }
    W(obj, 0x244 + 4 * slot2) = W(tbl, 0x10);
    W(obj, 0x2B8) = W(tbl, 0x10);

    m = MODE_A;
    if (m >= 0 && m <= 2) {
        tbl = SEC(P(obj, 4), 0x50);
    }
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m >= 0 && m <= 2) {
        W(obj, 0x188) = W(tbl, 0x10);
    }

    tbl = SEC(P(obj, 4), 0x30);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m >= 0 && m <= 2) {
        W(obj, 0x18C) = W(tbl, 0x10);
    }

    tbl = SEC(P(obj, 4), 0x4C);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m == 1 || m == 2) {
        W(obj, 0x1A0) = W(tbl, 0x10);
    } else if (m == 0) {
        W(obj, 0x1A4) = W(tbl, 0x10);
    }

    if (MODE_A == 0 && (FLAGS & 0x10) == 0) {
        tbl = SEC(P(obj, 4), 0xB8);
        Res_RelocateOffsets(&tbl, tbl, tbl);
        W(obj, 0x1A0) = W(tbl, 0x10);
        W(obj, 0x198) = W(tbl, 0x10) + 0x40;
    }

    m = MODE_A;
    if (m == 1 || m == 2) {
        hdr = P(obj, 4);
        P(obj, 0x174) = SEC(hdr, 0x2C);
        tbl = P(obj, 0x174);
        P(obj, 0x178) = SEC(hdr, 0xB8);
    } else if (m == 0) {
        tbl = SEC(P(obj, 4), 0x2C);
    }
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m == 0) {
        W(obj, 0x190) = W(tbl, 0x10);
        W(obj, 0x194) = W(tbl, 0x10);
    } else if (m >= 0 && m < 3) {
        W(obj, 0x194) = W(tbl, 0x10);
        W(obj, 0x198) = W(tbl, 0x10);
        W(obj, 0x19C) = W(tbl, 0x10);
    }

    tbl = SEC(P(obj, 4), 0xA0);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m == 1 || m == 2) {
        W(obj, 0x190) = W(tbl, 0x10);
    } else if (m == 0) {
        W(obj, 0x19C) = W(tbl, 0x10);
    }

    src = NULL;
    m = MODE_A;
    if (m >= 0 && m <= 2) {
        src = SEC(P(obj, 4), 0x54);
    }
    func_0026E7F0(obj + 0xF8, src, obj + 0x17C);
    if ((FLAGS & 0x10) == 0) {
        func_0026EAE0(obj + 0xF8, 60);
    }

    tbl = SEC(P(obj, 4), 0x24);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    W(obj, 0x1A8) = W(tbl, 0x10);
    W(obj, 0x1AC) = W(tbl, 0x10) + 0x40;
    func_0026E7F0(obj + 0xD0, SEC(P(obj, 4), 0x28), obj + 0x1A8);
    func_0026EAE0(obj + 0xD0, 60);

    /* MODE_B selects the layout variant: 0, 1, 2..3 */
    m = MODE_B;
    if (m == 1) {
        tbl = SEC(P(obj, 4), 0x48);
    } else if (m == 0) {
        tbl = SEC(P(obj, 4), 0x40);
    } else if (m >= 2 && m < 4) {
        tbl = SEC(P(obj, 4), 0x44);
    }
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_B;
    if (m == 1) {
        W(obj, 0x1B0) = W(tbl, 0x10);
        W(obj, 0x1B4) = W(tbl, 0x10) + 0x40;
        W(obj, 0x1B8) = W(tbl, 0x10) + 0x80;
        W(obj, 0x1BC) = W(tbl, 0x10) + 0xC0;
    } else if (m >= 2) {
        if (m < 4) {
            W(obj, 0x1B0) = W(tbl, 0x10);
            W(obj, 0x1B4) = W(tbl, 0x10) + 0x40;
            W(obj, 0x1B8) = W(tbl, 0x10) + 0x80;
        }
    } else if (m == 0) {
        W(obj, 0x1B0) = W(tbl, 0x10);
        W(obj, 0x1B4) = W(tbl, 0x10) + 0x40;
    }

    tbl = SEC(P(obj, 4), 0x9C);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_B;
    if (m == 1) {
        W(obj, 0x1C0) = W(tbl, 0x10);
    } else if (m >= 2) {
        if (m < 4) {
            W(obj, 0x1BC) = W(tbl, 0x10);
        }
    } else if (m == 0) {
        W(obj, 0x1B8) = W(tbl, 0x10);
    }

    tbl = SEC(P(obj, 4), 0x20);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_B;
    if (m == 1) {
        W(obj, 0x1CC) = W(tbl, 0x10);
    } else if (m >= 2) {
        if (m < 4) {
            W(obj, 0x1C8) = W(tbl, 0x10);
        }
    } else if (m == 0) {
        W(obj, 0x1C4) = W(tbl, 0x10);
    }
    W(obj, 0x21C) = W(tbl, 0x10);
    W(obj, 0x234) = W(tbl, 0x10);

    tbl = SEC(P(obj, 4), 0x8C);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_B;
    if (m == 1) {
        W(obj, 0x1C8) = W(tbl, 0x10);
    } else if (m >= 2) {
        if (m < 4) {
            W(obj, 0x1C4) = W(tbl, 0x10);
        }
    } else if (m == 0) {
        W(obj, 0x1C0) = W(tbl, 0x10);
    }
    W(obj, 0x218) = W(tbl, 0x10);
    W(obj, 0x230) = W(tbl, 0x10);

    tbl = SEC(P(obj, 4), 0x20);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_B;
    if (m == 1) {
        W(obj, 0x1CC) = W(tbl, 0x10);
    } else if (m >= 2) {
        if (m < 4) {
            W(obj, 0x1C8) = W(tbl, 0x10);
        }
    } else if (m == 0) {
        W(obj, 0x1C4) = W(tbl, 0x10);
    }
    W(obj, 0x21C) = W(tbl, 0x10);
    W(obj, 0x234) = W(tbl, 0x10);

    if (MODE_B != 0) {
        tbl = SEC(P(obj, 4), 0x18);
        Res_RelocateOffsets(&tbl, tbl, tbl);
        if (MODE_B == 1) {
            W(obj, 0x20C) = W(tbl, 0x10);
        } else {
            W(obj, 0x1FC) = W(tbl, 0x10);
        }
    }

    src = NULL;
    m = MODE_B;
    if (m == 1) {
        src = SEC(P(obj, 4), 0x3C);
    } else if (m == 0) {
        src = SEC(P(obj, 4), 0x34);
    } else if (m >= 2 && m < 4) {
        src = SEC(P(obj, 4), 0x38);
    }
    func_0026E7F0(obj + 0x30, src, obj + 0x1B0);

    tbl = SEC(P(obj, 4), 0x14);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    hdr = P(obj, 4);
    W(obj, 0x210) = W(tbl, 0x10);
    W(obj, 0x224) = W(tbl, 0x10) + 0x40;
    W(obj, 0x228) = W(tbl, 0x10);
    W(obj, 0x23C) = W(tbl, 0x10) + 0x80;
    func_0026E7F0(obj + 0x58, SEC(hdr, 0x60), obj + 0x210);
    func_0026E7F0(obj + 0x80, SEC(P(obj, 4), 0x64), obj + 0x228);

    tbl = SEC(P(obj, 4), 0x90);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    hdr = P(obj, 4);
    W(obj, 0x240) = W(tbl, 0x10);
    func_0026E7F0(obj + 0xA8, SEC(hdr, 0x94), obj + 0x240);
    if ((FLAGS & 0x10) != 0) {
        func_0026EAE0(obj + 0xA8, 60);
        func_0026EB78(obj + 0xA8, "fr_victory_or_defeat");
    }

    if (MODE_A == 0) {
        tbl = SEC(P(obj, 4), 0xBC);
        Res_RelocateOffsets(&tbl, tbl, tbl);
        W(obj, 0x244) = W(tbl, 0x10);
        W(obj, 0x250) = W(tbl, 0x10) + 0x40;
        W(obj, 0x24C) = W(tbl, 0x10) + 0x80;
    }

    /* four lists of (ptr, ptr+0x40) pairs; the slot depends on MODE_A */
    a = 0;
    tbl = SEC(P(obj, 4), 0x98);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m == 0) {
        a = 10;
    } else if (m >= 0 && m < 3) {
        a = 7;
    }
    W(obj, 0x244 + 4 * a) = W(tbl, 0x10);
    W(obj, 0x2A0) = W(tbl, 0x10);

    a = 0;
    tbl = SEC(P(obj, 4), 0x68);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m == 0) {
        a = 6;
    } else if (m >= 0 && m < 3) {
        a = 3;
    }
    W(obj, 0x244 + 4 * a) = W(tbl, 0x10);
    W(obj, 0x290) = W(tbl, 0x10);

    a = 0;
    b = 0;
    tbl = SEC(P(obj, 4), 0x70);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m == 0) {
        a = 9;
        b = 15;
    } else if (m >= 0 && m < 3) {
        a = 6;
        b = 12;
    }
    W(obj, 0x244 + 4 * a) = W(tbl, 0x10);
    W(obj, 0x244 + 4 * b) = W(tbl, 0x10) + 0x40;
    W(obj, 0x294) = W(tbl, 0x10);
    W(obj, 0x2B0) = W(tbl, 0x10) + 0x40;

    a = 0;
    tbl = SEC(P(obj, 4), 0x6C);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m == 0) {
        a = 16;
    } else if (m >= 0 && m < 3) {
        a = 13;
    }
    W(obj, 0x244 + 4 * a) = W(tbl, 0x10);
    W(obj, 0x2B4) = W(tbl, 0x10);
    W(obj, 0x2AC) = W(tbl, 0x10) + 0x40;

    __builtin_memset(idx, 0, 8);
    tbl = SEC(P(obj, 4), 0x7C);
    Res_RelocateOffsets(&tbl, tbl, tbl);
    m = MODE_A;
    if (m == 0) {
        idx[0] = 5;
        idx[1] = 4;
    } else if (m >= 0 && m < 3) {
        idx[0] = 2;
        idx[1] = 1;
    }
    W(obj, 0x244 + 4 * idx[0]) = W(tbl, 0x10);
    W(obj, 0x244 + 4 * idx[1]) = W(tbl, 0x10) + 0x40;

    src = NULL;
    m = MODE_A;
    if (m >= 0 && m <= 2) {
        src = SEC(P(obj, 4), 0x78);
    }
    func_0026E7F0(obj + 0x120, src, obj + 0x244);
    func_0026E7F0(obj + 0x148, SEC(P(obj, 4), 0x74), obj + 0x288);
    if ((FLAGS & 0x10) != 0) {
        func_0026EAE0(obj + 0x148, 60);
    }

    hdr = P(obj, 4);
    m = MODE_A;
    if (m == 1 || m == 0) {
        P(obj, 0x1C) = SEC(hdr, 0xB4);
        P(obj, 0x20) = SEC(hdr, 0xB0);
    } else if (m == 2) {
        P(obj, 0x1C) = SEC(hdr, 0xB4);
        P(obj, 0x20) = SEC(hdr, 0xB0);
        P(obj, 0x2C) = SEC(hdr, 0xBC);
    }
    P(obj, 0x24) = SEC(hdr, 4);
    P(obj, 0x28) = SEC(hdr, 8);
    P(obj, 0x18) = func_002B24C8(SEC(hdr, 0xC), NULL, NULL);

    i = 0;
    do {
        u8 *list = P(obj, 0x18);
        tbl = list + (W(list, 4 + 4 * i) & ~3);
        i++;
        Res_RelocateOffsets(&tbl, tbl, tbl);
    } while (i < 134);

    hdr = P(obj, 4);
    m = MODE_B;
    base_off = -1;
    if (m == 1) {
        base_off = 0x88;
    } else if (m == 0) {
        base_off = 0x80;
    } else if (m >= 2 && m < 4) {
        base_off = 0x84;
    }
    if (base_off != -1) {
        u8 *e = SEC(hdr, base_off);
        P(obj, 0x3304) = e + 4;
        W(obj, 0x3300) = W(e, 0);
    }
    P(obj, 0x2D4) = SEC(hdr, 0x10) + 4;
    W(obj, 0x2D0) = W(SEC(hdr, 0x10), 0);
    P(obj, 0x362C) = SEC(hdr, 0xAC) + 4;
    P(obj, 0x3630) = SEC(hdr, 0xA8) + 4;
    P(obj, 0x3634) = SEC(hdr, 0xA4) + 4;
    return P(obj, 0x3634);
}
