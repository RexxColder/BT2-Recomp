#include "common.h"

s32 func_002DC538(u8 *arg0);

/* MSB-first bit reader over a pair of big-endian words (cur = window, nxt = following word).
 * pos = bits of the window already used, p = next word to load. */
#define LOADW(dst)                                                          \
    do {                                                                    \
        dst = ((u32)(s32)(s8)p[0] << 24) | ((u32)p[1] << 16) |              \
              ((u32)p[2] << 8) | (u32)p[3];                                 \
        p += 4;                                                             \
    } while (0)

/* read n bits into dst */
#define GETBITS(dst, n)                                                     \
    do {                                                                    \
        if (pos < 32 - (n)) {                                               \
            dst = cur >> (32 - (n));                                        \
            cur <<= (n);                                                    \
            pos += (n);                                                     \
        } else {                                                            \
            pos -= 32 - (n);                                                \
            if (pos != 0) {                                                 \
                dst = (cur | (nxt >> ((n) - pos))) >> (32 - (n));      \
                cur = nxt << pos;                                           \
            } else {                                                        \
                dst = cur >> (32 - (n));                                    \
                cur = nxt;                                                  \
            }                                                               \
            LOADW(nxt);                                                     \
        }                                                                   \
    } while (0)

/* skip n bits */
#define SKIPBITS(n)                                                         \
    do {                                                                    \
        pos += (n);                                                         \
        if (pos < 32) {                                                     \
            cur <<= (n);                                                    \
        } else {                                                            \
            pos -= 32;                                                      \
            cur = nxt << pos;                                               \
            LOADW(nxt);                                                     \
        }                                                                   \
    } while (0)

/* Parses a header (fields into ctx+0x28.., a list of (byte, bit, 13-bit) entries) from the bit stream at
 * data+4; *outLen = bytes used; calls the callback at ctx+0xE4 (arg ctx+0xE8) with the parsed record. */
s32 func_002DB060(u8 *ctx, u8 *data, s32 *outLen) {
    u8 rec[16];
    s32 n;
    u8 list[192];
    u8 *hdr = ctx + 0x28;
    u8 *p = (u8 *)(((u32)data + 4) & 0xFFFFFFFC);
    s32 pos = (s32)(((u32)data + 4) - (u32)p) << 3;
    u32 cur, nxt;
    u32 f;
    u32 flags;
    u32 e0, e1, e2;
    s32 v;
    s32 end;
    s32 (*cb)(s32, u8 *, s32, s32);

    LOADW(cur);
    LOADW(nxt);
    cur <<= pos;

    GETBITS(f, 16);
    *(u32 *)(hdr + 0x0) = f;
    SKIPBITS(1);
    GETBITS(f, 22);
    *(u32 *)(hdr + 0x4) = f;
    SKIPBITS(1);
    GETBITS(f, 6);
    *(u32 *)(hdr + 0x8) = f;
    GETBITS(f, 1);
    *(u32 *)(hdr + 0x10) = f;
    GETBITS(f, 1);
    *(u32 *)(hdr + 0x14) = f;
    GETBITS(f, 1);
    *(u32 *)(hdr + 0x18) = f;
    GETBITS(f, 1);
    *(u32 *)(hdr + 0x1C) = f;
    SKIPBITS(1);
    GETBITS(f, 5);
    *(u32 *)(hdr + 0xC) = f;
    GETBITS(flags, 8);

    n = 0;
    if ((s32)cur < 0) {
        do {
            GETBITS(e0, 8);
            SKIPBITS(2);
            GETBITS(e1, 1);
            GETBITS(e2, 13);
            list[n * 4 + 0] = (u8)e0;
            list[n * 4 + 1] = (u8)e1;
            *(u16 *)(list + n * 4 + 2) = (u16)e2;
            n = n + 1;
        } while ((s32)cur < 0);
    }

    end = (s32)(u32)p + ((pos + 7) >> 3);
    *outLen = (end - 8) - (s32)(u32)data;
    v = func_002DC538((u8 *)(u32)(end - 8));
    if (v == 0) {
        v = func_002DC538((u8 *)(u32)(end - 7));
        if (v == 0x40000) {
            *outLen = *outLen + 1;
            v = *outLen;
        }
    }
    cb = *(s32 (**)(s32, u8 *, s32, s32))(ctx + 0xE4);
    if (cb != 0) {
        u8 b18 = hdr[0x18];
        u8 b0c = hdr[0x0C];
        u8 b08 = hdr[0x08];
        u8 b10 = hdr[0x10];
        u8 b14 = hdr[0x14];
        u8 b1c = hdr[0x1C];
        *(u32 *)(rec + 0) = *(u32 *)(hdr + 4);
        rec[4] = b08;
        rec[5] = b10;
        rec[6] = b14;
        rec[7] = b18;
        rec[8] = b1c;
        rec[9] = b0c;
        rec[10] = (u8)(flags >> 7);
        rec[11] = (u8)(flags & 0x7F);
        *(s32 *)(rec + 12) = n;
        v = cb(*(s32 *)(ctx + 0xE8), rec, b1c, b08);
    }
    return v;
}
