#include "common.h"

extern void func_003061A8(u8 *buf, s32 pos, u8 *buf2, u8 *out);

/* Big-endian bit reader over a byte stream: `cur` holds the current 32-bit window (MSB first, `bp` bits already
   consumed), `nxt` the following word, `p` points past `nxt`. */
typedef struct {
    u32 cur;
    u32 nxt;
    u8 *p;
    s32 bp;
} BitReader;

static u32 br_word(u8 *p) {
    return ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | (u32)p[3];
}

static u32 br_take(BitReader *r, s32 n) {
    u32 v;
    if (r->bp + n >= 32) {
        s32 nb = r->bp + n - 32;
        if (nb != 0) {
            v = (r->cur | (r->nxt >> (n - nb))) >> (32 - n);
            r->cur = r->nxt << nb;
        } else {
            v = r->cur >> (32 - n);
            r->cur = r->nxt;
        }
        r->nxt = br_word(r->p);
        r->p += 4;
        r->bp = nb;
    } else {
        v = r->cur >> (32 - n);
        r->cur <<= n;
        r->bp += n;
    }
    return v;
}

/* Parses one MPEG picture-header-like record from the stream buffer ctx+0x38C (len ctx+0x390), fills the
   header fields of ctx and hands the consumed part to func_003061A8 / the stream object's callbacks.
   Returns 0 on success, -3 when the extension bits run past the buffer. */
s32 func_002DF0A0(u8 *ctx, u8 *obj) {
    u8 *buf = ctx + 0x38C;
    u8 out[16];
    BitReader r;
    u8 *vt;
    u32 bufStart;
    u32 mode;
    s32 hdr;
    s32 pos;
    u8 *aligned;
    s32 k;

    *(s32 *)(ctx + 0x3B8) = 3;
    vt = *(u8 **)obj;
    ((void (*)(u8 *, s32, s32, u8 *))*(u8 **)(vt + 0x18))(obj, 1, 0x7FFFFFFF, buf);

    bufStart = *(u32 *)buf;
    aligned = (u8 *)(bufStart & ~3u);
    r.bp = (s32)((bufStart - (bufStart & ~3u)) * 8);
    r.cur = br_word(aligned + 4);
    if (r.bp != 0) {
        r.cur <<= r.bp;
    }
    r.nxt = br_word(aligned + 8);
    r.p = aligned + 12;

    *(u32 *)(ctx + 0x1E4) = br_take(&r, 10);
    *(u32 *)(ctx + 0x1E8) = br_take(&r, 3);
    *(u32 *)(ctx + 0x2BC) = br_take(&r, 16);

    mode = *(u32 *)(ctx + 0x1E8);
    hdr = *(s32 *)(ctx + 0x3FC);
    if (mode - 1 < 2) {
        *(s32 *)(ctx + 0x400) = 0;
        *(s32 *)(ctx + 0x3FC) = hdr + 1;
        *(s32 *)(ctx + 0x238) = (hdr + 1) << 16;
    } else {
        s32 n = *(s32 *)(ctx + 0x400) + 1;
        *(s32 *)(ctx + 0x400) = n;
        *(s32 *)(ctx + 0x238) = ((hdr - 1) << 16) | n;
    }
    if (mode - 2 < 2) {
        *(u32 *)(ctx + 0x2F0) = br_take(&r, 1);
        k = (s32)br_take(&r, 3) - 1;
        *(s32 *)(ctx + 0x2F8) = 0x1B - k;
        *(s32 *)(ctx + 0x2FC) = 1 << k;
        *(s32 *)(ctx + 0x2F4) = k;
    }
    if (mode == 3) {
        *(u32 *)(ctx + 0x314) = br_take(&r, 1);
        k = (s32)br_take(&r, 3) - 1;
        *(s32 *)(ctx + 0x31C) = 0x1B - k;
        *(s32 *)(ctx + 0x320) = 1 << k;
        *(s32 *)(ctx + 0x318) = k;
    }
    *(s32 *)(ctx + 0x2D4) = *(s32 *)(ctx + 0x2DC);
    bufStart = *(u32 *)buf;

    /* skip extension bytes: each set top bit is followed by 8 more bits */
    while ((s32)r.cur < 0) {
        r.bp += 9;
        if (r.bp < 32) {
            r.cur <<= 9;
        } else {
            r.bp -= 32;
            r.cur = r.nxt << r.bp;
            r.nxt = br_word(r.p);
            r.p += 4;
        }
        if ((s32)((u32)r.p + ((r.bp + 7) >> 3) - 8 - bufStart) >= *(s32 *)(ctx + 0x390)) {
            return -3;
        }
    }
    r.bp += 1;
    if (r.bp >= 32) {
        r.bp -= 32;
        r.p += 4;
    }
    pos = (s32)((u32)r.p + ((r.bp + 7) >> 3) - 8 - bufStart);
    func_003061A8(buf, pos, buf, out);
    vt = *(u8 **)obj;
    ((void (*)(u8 *, s32, u8 *))*(u8 **)(vt + 0x20))(obj, 0, buf);
    vt = *(u8 **)obj;
    ((void (*)(u8 *, s32, u8 *))*(u8 **)(vt + 0x1C))(obj, 1, out);
    return 0;
}
