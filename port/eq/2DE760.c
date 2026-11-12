#include "common.h"

/* 0x002DE760: parses a stream header (12+12 bit size, 4 bit code, 4, 18, skip 1, 10, 1, two matrix flags with
 * 64-byte skips) from the big-endian bitstream at obj+0x38C, then reports the consumed bytes to the reader. */
s32 func_003061A8(u8 *a, s32 b, u8 *c, u8 *d);

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

s32 func_002DE760(u8 *obj, u8 *reader) {
    u8 sp[16];
    u8 *hdr = obj + 0x1D0;
    u8 *ptrfield = obj + 0x38C;
    BitRd bs;
    u32 addr;
    u8 *base;
    s32 flag;
    s32 i;

    *(s32 *)(obj + 0x3B8) = 1;
    *(s32 *)(hdr + 0x34) = *(s32 *)(hdr + 0x34) + 1;
    *(s32 *)(obj + 0x3FC) = 0;
    *(s32 *)(obj + 0x400) = 0;
    *(s32 *)(hdr + 0x68) = 0;
    ((s32 (*)(u8 *, s32, s32, u8 *))(*(u32 *)(*(u8 **)reader + 0x18)))(reader, 1, 0x7FFFFFFF, ptrfield);

    addr = *(u32 *)ptrfield;
    base = (u8 *)(addr & ~3u) + 4;
    bs.pos = (s32)(addr - (addr & ~3u)) * 8;
    bs.cur = bs_load(base);
    if (bs.pos != 0) {
        bs.cur = bs.cur << bs.pos;
    }
    bs.next = bs_load(base + 4);
    bs.ptr = base + 8;

    *(u32 *)(hdr + 0x00) = bs_bits(&bs, 12);
    *(u32 *)(hdr + 0x04) = bs_bits(&bs, 12);
    *(u32 *)(obj + 0x2A4) = bs_bits(&bs, 4);
    *(u32 *)(hdr + 0x10) = bs_bits(&bs, 4);
    *(u32 *)(obj + 0x2A8) = bs_bits(&bs, 18);
    bs_bits(&bs, 1);
    *(u32 *)(obj + 0x2AC) = bs_bits(&bs, 10);
    *(u32 *)(obj + 0x2B0) = bs_bits(&bs, 1);

    flag = (s32)bs_bits(&bs, 1);
    if (flag != 0) {
        for (i = 63; i >= 0; i--) {
            bs_bits(&bs, 8);
        }
    }

    /* second matrix flag: consumed without refilling, then 64 bytes skipped */
    flag = (s32)(bs.cur >> 31);
    if (bs.pos == 31) {
        bs.pos = 0;
        bs.ptr += 4;
    } else {
        bs.pos += 1;
    }
    if (flag != 0) {
        for (i = 63; i >= 0; i--) {
            if (bs.pos < 24) {
                bs.pos += 8;
            } else {
                bs.pos -= 24;
                bs.ptr += 4;
            }
        }
    }

    *(s32 *)(hdr + 0x08) = ((s32)*(u32 *)(hdr + 0x00) + 15) >> 4;
    *(s32 *)(hdr + 0x0C) = ((s32)*(u32 *)(hdr + 0x04) + 15) >> 4;
    *(s32 *)(obj + 0x344) = *(s32 *)(hdr + 0x0C) * *(s32 *)(hdr + 0x08) - 1;
    *(u32 *)(hdr + 0x48) = *(u32 *)(obj + 0x2A8);
    *(u32 *)(hdr + 0x4C) = *(u32 *)(obj + 0x2AC);
    hdr[0x59] = obj[0x2A4];
    hdr[0x5A] = obj[0x2B0];
    func_003061A8(ptrfield, (s32)((u32)(bs.ptr + ((bs.pos + 7) >> 3) - 8) - *(u32 *)(obj + 0x38C)), ptrfield, sp);
    ((s32 (*)(u8 *, s32, u8 *))(*(u32 *)(*(u8 **)reader + 0x20)))(reader, 0, ptrfield);
    ((s32 (*)(u8 *, s32, u8 *))(*(u32 *)(*(u8 **)reader + 0x1C)))(reader, 1, sp);
    return 0;
}
