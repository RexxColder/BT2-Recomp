#include "common.h"

/* Bitstream header parser. Returns the byte position (in the stream at `stream`) just after the parsed bits.
 * The bit reader keeps `cur` = bits not yet consumed (left aligned), `nxt` = the following word, `k` = bits of
 * cur already consumed, `p` = address of the word after nxt. */
extern s32 D_0037B170[] __attribute__((section(".data")));
extern void func_002E25B8(u8 *ctx);
extern void func_002E2668(u8 *ctx);
extern void func_002E26B8(u8 *ctx);
extern void func_002E2728(u8 *ctx);

typedef struct {
    u32 cur;
    u32 nxt;
    s32 k;
    u8 *p;
} Bits;

static u32 bits_word(u8 *p) {
    return ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | (u32)p[3];
}

/* Reads n bits (1..31). */
static u32 bits_get(Bits *b, s32 n) {
    u32 v;
    if (b->k < 32 - n) {
        v = b->cur >> (32 - n);
        b->cur <<= n;
        b->k += n;
        return v;
    }
    b->k -= 32 - n;
    if (b->k != 0) {
        v = (b->cur | (b->nxt >> (n - b->k))) >> (32 - n);
        b->cur = b->nxt << b->k;
    } else {
        v = b->cur >> (32 - n);
        b->cur = b->nxt;
    }
    b->nxt = bits_word(b->p);
    b->p += 4;
    return v;
}

/* Skips 64 bytes, 8 bits at a time. */
static void bits_skip64(Bits *b) {
    s32 i;
    for (i = 63; i >= 0; i--) {
        b->k += 8;
        if (b->k >= 32) {
            b->k -= 32;
            b->cur = b->nxt << b->k;
            b->nxt = bits_word(b->p);
            b->p += 4;
        } else {
            b->cur <<= 8;
        }
    }
}

#define F(o) (*(s32 *)(s + (o)))

u8 *func_002E33F8(u8 *ctx, u8 *stream) {
    u8 *s = ctx + 0x160;
    u8 *base;
    s32 off;
    s32 type;
    s32 x;
    s32 i;
    u32 w0;
    u32 w1;
    Bits b;

    off = (u32)stream & 3;
    base = stream - off;
    F(0x438) += 1;

    w1 = bits_word(base + 4);
    w0 = bits_word(base) << (8 * off);
    if (off != 0) {
        F(0x34) = w0 | (w1 >> (32 - 8 * off));
        b.cur = w1 << (8 * off);
    } else {
        F(0x34) = w0;
        b.cur = w1;
    }
    b.nxt = bits_word(base + 8);
    b.p = base + 12;
    b.k = 8 * off;

    F(0x40) = bits_get(&b, 4);
    type = F(0x40);

    if (F(0x308) != 0 && F(0x308) != 16) {
        F(0x494) += 1;
    } else if (F(0x30C) != 0 && F(0x30C) != type) {
        F(0x494) += 1;
    }

    if (F(0x420) != 1 && (type == 1 || type == 2 || type == 5)) {
        F(0x494) += 1;
    } else if (F(0x420) != 3 && (type == 3 || type == 4 || type == 7 || type == 8 || type == 9 || type == 10)) {
        F(0x494) += 1;
    }

    switch (type - 1) {
    case 0:
        F(0x44) = bits_get(&b, 8);
        F(0x48) = bits_get(&b, 1);
        F(0x4C) = bits_get(&b, 2);
        F(0x50) = bits_get(&b, 2);
        F(0x54) = bits_get(&b, 2);
        F(0x58) = bits_get(&b, 12);
        F(0x18) = bits_get(&b, 1);
        F(0x5C) = bits_get(&b, 8);
        F(0x60) = bits_get(&b, 1);
        F(0x64) = bits_get(&b, 2);
        F(0x68) = bits_get(&b, 5);
        if (F(0x4C) != 1) {
            F(0x4C) = 1;
            F(0x494) += 1;
        }
        F(0x318) = D_0037B170[1];
        func_002E25B8(s);
        F(0x2D4) = (F(0x58) << 18) | F(0x14);
        F(0x2D8) = (F(0x5C) << 10) | F(0x1C);
        break;
    case 1:
        F(0x6C) = bits_get(&b, 3);
        F(0x70) = bits_get(&b, 1);
        if (F(0x70) != 0) {
            F(0x74) = bits_get(&b, 8);
            F(0x78) = bits_get(&b, 8);
            F(0x7C) = bits_get(&b, 8);
        }
        F(0x80) = bits_get(&b, 14);
        F(0x18) = bits_get(&b, 1);
        F(0x84) = bits_get(&b, 14);
        break;
    case 2:
        F(0x24) = bits_get(&b, 1);
        if (F(0x24) != 0) {
            bits_skip64(&b);
        }
        F(0x28) = bits_get(&b, 1);
        if (F(0x28) != 0) {
            bits_skip64(&b);
        }
        F(0x158) = bits_get(&b, 1);
        if (F(0x158) != 0) {
            bits_skip64(&b);
        }
        /* last flag: no bits are kept, only the position moves */
        if (b.k < 31) {
            b.k += 1;
            F(0x15C) = b.cur >> 31;
        } else {
            b.k -= 31;
            if (b.k != 0) {
                F(0x15C) = (b.cur | (b.nxt >> (1 - b.k))) >> 31;
            } else {
                F(0x15C) = b.cur >> 31;
            }
            b.p += 4;
        }
        if (F(0x15C) != 0) {
            for (i = 63; i >= 0; i--) {
                b.k += 8;
                if (b.k >= 32) {
                    b.k -= 32;
                    b.p += 4;
                }
            }
        }
        func_002E2728(s);
        break;
    case 3:
        F(0x19C) = bits_get(&b, 1);
        F(0x1A0) = bits_get(&b, 8);
        F(0x1A4) = bits_get(&b, 1);
        F(0x1A8) = bits_get(&b, 7);
        F(0x18) = bits_get(&b, 1);
        F(0x1AC) = bits_get(&b, 20);
        F(0x18) = bits_get(&b, 1);
        F(0x1B0) = bits_get(&b, 22);
        F(0x18) = bits_get(&b, 1);
        F(0x1B4) = bits_get(&b, 22);
        break;
    case 4:
        F(0x310) = 1;
        F(0x88) = bits_get(&b, 2);
        F(0x8C) = bits_get(&b, 4);
        x = F(0x88);
        if (x == 1) {
            F(0x90) = bits_get(&b, 14);
            F(0x18) = bits_get(&b, 1);
            F(0x94) = bits_get(&b, 14);
            F(0x98) = bits_get(&b, 5);
            F(0x9C) = bits_get(&b, 5);
            F(0xA0) = bits_get(&b, 5);
            F(0xA4) = bits_get(&b, 5);
        } else if (x == 3) {
            F(0xA8) = bits_get(&b, 1);
            if (F(0xA8) != 0) {
                F(0xAC) = bits_get(&b, 1);
            }
            F(0xB0) = bits_get(&b, 3);
            F(0xB4) = bits_get(&b, 3);
        }
        break;
    case 6:
        func_002E2668(s);
        for (i = 0; i < F(0x38); i++) {
            F(0x160 + 4 * i) = bits_get(&b, 16);
            F(0x18) = bits_get(&b, 1);
            F(0x16C + 4 * i) = bits_get(&b, 16);
            F(0x18) = bits_get(&b, 1);
        }
        break;
    case 7:
        F(0x104) = bits_get(&b, 4);
        F(0x108) = bits_get(&b, 4);
        F(0x10C) = bits_get(&b, 4);
        F(0x110) = bits_get(&b, 4);
        F(0x114) = bits_get(&b, 2);
        F(0x118) = bits_get(&b, 2);
        F(0x11C) = bits_get(&b, 1);
        F(0x120) = bits_get(&b, 1);
        F(0x124) = bits_get(&b, 1);
        F(0x128) = bits_get(&b, 1);
        F(0x12C) = bits_get(&b, 1);
        F(0x130) = bits_get(&b, 1);
        F(0x134) = bits_get(&b, 1);
        F(0x138) = bits_get(&b, 1);
        F(0x13C) = bits_get(&b, 1);
        F(0x140) = bits_get(&b, 1);
        if (F(0x140) != 0) {
            F(0x144) = bits_get(&b, 1);
            F(0x148) = bits_get(&b, 3);
            F(0x14C) = bits_get(&b, 1);
            F(0x150) = bits_get(&b, 7);
            F(0x154) = bits_get(&b, 8);
        }
        func_002E25B8(s);
        func_002E26B8(s);
        if (F(0x3C4) == 0) {
            *(s32 *)(ctx + 0x154) = 0;
        }
        break;
    case 8:
        F(0x314) = 1;
        F(0x184) = bits_get(&b, 10);
        F(0x18) = bits_get(&b, 1);
        F(0x188) = bits_get(&b, 15);
        F(0x18) = bits_get(&b, 1);
        F(0x18C) = bits_get(&b, 15);
        F(0x190) = bits_get(&b, 2);
        F(0x194) = bits_get(&b, 1);
        F(0x198) = bits_get(&b, 1);
        break;
    case 9:
        F(0x178) = bits_get(&b, 2);
        F(0x17C) = bits_get(&b, 10);
        F(0x18) = bits_get(&b, 1);
        F(0x180) = bits_get(&b, 10);
        break;
    default:
        F(0x494) += 1;
        break;
    }

    F(0x30C) = 0;
    F(0x308) = 0;
    x = b.k + 8 * (s32)(b.p - stream);
    i = x - 57;
    if (i < 0) {
        i = x - 50;
    }
    return stream + (i >> 3);
}
