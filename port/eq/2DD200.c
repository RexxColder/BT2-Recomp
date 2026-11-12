#include "common.h"

extern s16 D_0037AF88[];

/* Big-endian bit reader over an unaligned byte stream: cur holds the current word shifted left by
   pos consumed bits, nxt is the next word. */
typedef struct {
    u32 cur;
    u32 nxt;
    s32 pos;
    u8 *p;
} BitRd;

static u32 rd32be(u8 *p) {
    return ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | (u32)p[3];
}

static u32 br_peek(BitRd *b, s32 n) {
    u32 v = b->cur >> (32 - n);
    if (b->pos >= 33 - n) {
        v |= b->nxt >> (64 - n - b->pos);
    }
    return v;
}

static void br_skip(BitRd *b, s32 n) {
    b->pos += n;
    if (b->pos < 32) {
        b->cur <<= n;
    } else {
        b->pos -= 32;
        b->cur = b->nxt << b->pos;
        b->nxt = rd32be(b->p);
        b->p += 4;
    }
}

/* 0x002DD200 (a0 = stream, a1 = available size, a2 = count): checks a stream header: start code
   0x101, two flag bits (0 then 1), a 6-bit code 0xB / 0x16 / 0x17, a run of 11-bit 8s, then a
   table-coded field whose value must equal the table's high byte, and a final 6-bit code. Returns
   1 when the header fits in a1 bytes. */
s32 func_002DD200(u8 *a0, s64 a1, s32 a2) {
    BitRd b;
    u32 w0;
    u32 w1;
    u32 code;
    s32 n;
    s32 v;
    s32 tab;
    s32 bits;
    u32 got;
    u8 *base = (u8 *)((u32)a0 & ~3u);

    b.pos = (s32)((u32)a0 - (u32)base) * 8;
    w0 = rd32be(base);
    w1 = rd32be(base + 4);
    if (b.pos == 0) {
        code = w0;
        b.cur = w1;
    } else {
        code = (w0 << b.pos) | (w1 >> (32 - b.pos));
        b.cur = w1 << b.pos;
    }
    b.nxt = rd32be(base + 8);
    b.p = base + 12;
    if (code != 0x101) {
        return 0;
    }
    br_skip(&b, 5);
    got = b.cur >> 31;
    br_skip(&b, 1);
    if (got != 0) {
        return 0;
    }
    got = b.cur >> 31;
    br_skip(&b, 1);
    if (got == 0) {
        return 0;
    }
    code = br_peek(&b, 6);
    if (code == 0xB) {
        br_skip(&b, 6);
    } else if (code >= 0xB && code < 0x18 && code >= 0x16) {
        br_skip(&b, 5);
    } else {
        return 0;
    }
    n = a2 - 1;
    for (;;) {
        got = br_peek(&b, 11);
        v = n - 1;
        if (got != 8) {
            break;
        }
        br_skip(&b, 11);
        n -= 0x21;
        if (n < 0x22) {
            v = n - 1;
            break;
        }
    }
    if ((u32)v > 0x20) {
        return 0;
    }
    tab = D_0037AF88[n];
    bits = tab & 0xFF;
    got = br_peek(&b, bits);
    br_skip(&b, bits);
    if ((s32)got != (tab >> 8)) {
        return 0;
    }
    code = br_peek(&b, 6);
    if (code == 0xB) {
        b.pos += 6;
    } else if (code >= 0xB && code < 0x18 && code >= 0x16) {
        b.pos += 5;
    } else {
        return 0;
    }
    if (b.pos >= 32) {
        b.pos -= 32;
        b.p += 4;
    }
    return a1 >= (s64)((b.p + ((b.pos + 7) >> 3)) - 8 - a0);
}
