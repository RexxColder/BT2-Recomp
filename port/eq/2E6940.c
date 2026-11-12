#include "common.h"

/* 0x002E6940: reads a big-endian bitstream header (32, 10, 3, 16 bits, then conditional fields chosen by the
 * 3-bit type at +0x1E0 = ctx[0xE0], and a loop of 8-bit items while a 1-bit continue flag is set), updates
 * counters, and returns the address of the first byte not fully consumed. */

/* bit reader state: cur holds the unread bits at the top, next the following word, pos = bits used of cur */
typedef struct {
    u32 cur;
    u32 next;
    s32 pos;
    u8 *ptr;
} BitRd;

static u32 bs_load(u8 *p) {
    return ((u32)(s32)(s8)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | (u32)p[3];
}

static u32 bs_bits(BitRd *b, s32 n) {
    u32 v;
    s32 p;

    if (b->pos + n < 32) {
        v = b->cur >> (32 - n);
        b->cur <<= n;
        b->pos += n;
        return v;
    }
    p = b->pos + n - 32;
    v = (b->cur | (b->next >> (n - p))) >> (32 - n);
    b->cur = b->next << p;
    b->next = bs_load(b->ptr);
    b->ptr += 4;
    b->pos = p;
    return v;
}

u8 *func_002E6940(u8 *obj, u8 *stream) {
    u8 *c = obj + 0x160;
    BitRd bs;
    u8 *base;
    s32 type;
    s32 cnt;
    s32 bits;
    s32 adj;
    s32 d;

    *(s32 *)(c + 0x420) = 3;
    *(s32 *)(c + 0x440) = *(s32 *)(c + 0x440) + 1;
    d = *(s32 *)(c + 0x308);
    if (d == 0 || d == 4) {
        if (*(s32 *)(c + 0x30C) != 0) {
            *(s32 *)(c + 0x494) = *(s32 *)(c + 0x494) + 1;
        }
    } else {
        *(s32 *)(c + 0x494) = *(s32 *)(c + 0x494) + 1;
    }

    base = (u8 *)((u32)stream & ~3u);
    bs.pos = ((u32)stream - (u32)base) * 8;
    bs.cur = bs_load(base);
    bs.next = bs_load(base + 4);
    bs.ptr = base + 8;
    if (bs.pos != 0) {
        *(u32 *)(c + 0xD8) = (bs.cur << bs.pos) | (bs.next >> (32 - bs.pos));
        bs.cur = bs.next << bs.pos;
    } else {
        *(u32 *)(c + 0xD8) = bs.cur;
        bs.cur = bs.next;
    }
    bs.next = bs_load(bs.ptr);
    bs.ptr += 4;

    *(u32 *)(c + 0xDC) = bs_bits(&bs, 10);
    *(u32 *)(c + 0xE0) = bs_bits(&bs, 3);
    *(u32 *)(c + 0xE4) = bs_bits(&bs, 16);

    type = *(s32 *)(c + 0xE0);
    if ((u32)(type - 1) >= 3) {
        *(s32 *)(c + 0x494) = *(s32 *)(c + 0x494) + 1;
    }
    if ((u32)(type - 1) < 2) {
        *(s32 *)(c + 0x4A8) = 0;
        *(s32 *)(c + 0x4A4) = *(s32 *)(c + 0x4A4) + 1;
        *(s32 *)(c + 0x4AC) = *(s32 *)(c + 0x4A4) << 16;
    } else {
        *(s32 *)(c + 0x4A8) = *(s32 *)(c + 0x4A8) + 1;
        *(s32 *)(c + 0x4AC) = ((*(s32 *)(c + 0x4A4) - 1) << 16) | *(s32 *)(c + 0x4A8);
    }

    if ((u32)(type - 2) < 2) {
        *(u32 *)(c + 0xE8) = bs_bits(&bs, 1);
        *(u32 *)(c + 0xEC) = bs_bits(&bs, 3);
    }
    if (type == 3) {
        *(u32 *)(c + 0xF0) = bs_bits(&bs, 1);
        *(u32 *)(c + 0xF4) = bs_bits(&bs, 3);
    }

    *(u32 *)(c + 0xF8) = bs_bits(&bs, 1);
    while (*(s32 *)(c + 0xF8) != 0) {
        *(u32 *)(c + 0xFC) = bs_bits(&bs, 8);
        *(u32 *)(c + 0xF8) = bs_bits(&bs, 1);
    }

    bits = bs.pos + ((s32)((u32)bs.ptr - (u32)stream)) * 8;
    adj = bits - 0x39;
    if (adj < 0) {
        adj = bits - 0x32;
    }
    *(s32 *)(c + 0x444 + type * 4) = *(s32 *)(c + 0x444 + type * 4) + 1;
    *(s32 *)(c + 0x30C) = 8;
    *(s32 *)(c + 0x308) = 0x10;
    return stream + (adj >> 3);
}
