#include "common.h"

/* Next n (<= 32) bits of a big-endian bit stream, starting at bit `pos` of `s` (not consumed). */
static u32 PeekBits(const u8 *s, u32 pos, u32 n) {
    u64 v = 0;
    u32 i;
    u32 byte = pos >> 3;

    for (i = 0; i < 5; i++) {
        v = (v << 8) | s[byte + i];
    }
    return (u32)((v >> (40 - (pos & 7) - n)) & (((u64)1 << n) - 1));
}

/* 33 bit time stamp: '0010'/'0011' prefix, then 3 + 15 + 15 bits each followed by a marker bit */
#define READ_STAMP(dst, s, pos) \
    do { \
        u64 hi; \
        u64 mid; \
        u64 lo; \
        (pos) += 4; \
        hi = PeekBits((s), (pos), 3); \
        (pos) += 3 + 1; \
        mid = PeekBits((s), (pos), 15); \
        (pos) += 15 + 1; \
        lo = PeekBits((s), (pos), 15); \
        (pos) += 15 + 1; \
        (dst) = ((hi & 7) << 30) | ((mid & 0x7FFF) << 15) | (lo & 0x7FFF); \
    } while (0)

/* Parses a PES packet header (stream id, packet length, optional P-STD and PTS/DTS) of the byte stream at
   src + 3 and stores the parsed fields at ctx + 0xA8. *outLen gets the header length (or the fixed
   length for the private/padding ids); returns the number of bytes consumed from src. */
s32 func_002DB8D0(u8 *ctx, u8 *src, s32 *outLen, s32 mode) {
    u8 *base = ctx + 0xA8;
    const u8 *s = src + 3;
    u32 pos = 0;
    s32 id;
    s32 kind;
    s32 sub;
    s32 hdr;
    s32 res;
    u32 t;

    id = (s32)PeekBits(s, pos, 8);
    pos += 8;
    *(s32 *)(base + 0x10) = id;
    if ((u32)(id - 0xE0) < 0x10) {
        kind = 1;
        sub = id - 0xE0;
    } else if ((u32)(id - 0xC0) < 0x20) {
        kind = 0;
        sub = id - 0xC0;
    } else if (id == 0xBD) {
        kind = 2;
        sub = 1;
    } else if (id == 0xBF) {
        kind = 2;
        sub = 2;
    } else {
        kind = (id == 0xBE) ? 3 : 4;
        sub = 0;
    }
    *(s32 *)(base + 0x14) = kind;
    *(s32 *)(base + 0x18) = sub;

    if (mode == 2) {
        *(s32 *)(base + 0x1C) = (s32)PeekBits(s, pos, 16);
        pos += 16;
        hdr = 6;
    } else {
        *(s32 *)(base + 0x1C) = (s32)PeekBits(s, pos, 32);
        pos += 32;
        hdr = 8;
    }
    if ((u32)(id - 0xBE) < 2) {
        *outLen = hdr;
        res = *(s32 *)(base + 0x1C);
        *(s32 *)(base + 0x24) = res;
        return res;
    }

    /* stuffing bytes */
    while (PeekBits(s, pos, 8) == 0xFF) {
        pos += 8;
    }
    /* P-STD buffer size */
    if (PeekBits(s, pos, 2) == 1) {
        u32 scale;
        u32 size;
        pos += 2;
        scale = PeekBits(s, pos, 1);
        pos += 1;
        size = PeekBits(s, pos, 13) << 7;
        pos += 13;
        if (scale != 0) {
            size *= 8;
        }
        *(s32 *)(base + 0x20) = (s32)size;
    }
    /* time stamps */
    t = PeekBits(s, pos, 4);
    if (t == 2) {
        u64 pts;
        READ_STAMP(pts, s, pos);
        *(u64 *)(base + 8) = ~(u64)0;
        *(u64 *)(base + 0) = pts;
    } else if (t == 3) {
        u64 pts;
        u64 dts;
        READ_STAMP(pts, s, pos);
        *(u64 *)(base + 0) = pts;
        READ_STAMP(dts, s, pos);
        *(u64 *)(base + 8) = dts;
    } else {
        pos += 8;
        *(u64 *)(base + 8) = ~(u64)0;
        *(u64 *)(base + 0) = ~(u64)0;
    }

    res = 3 + (s32)((pos + 7) >> 3);
    *outLen = res;
    *(s32 *)(base + 0x24) = *(s32 *)(base + 0x1C) + hdr - res;
    return res;
}
