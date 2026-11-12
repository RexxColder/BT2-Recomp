#include "common.h"

s32 func_00277E68(s32 arg0);

/* 0x002786A0: GS packet builder. Zeroes the first qword of out (arg0), then for every 14-word record of arg1 whose
 * word0 bit 0 is set, writes four qwords at the output cursor: a tag (word10 | (word13 * alpha) << 24 |
 * word12 << 16 | word11 << 8) with a zero high half; a qword that is (0, 0x46) when word0 bit 2 is set, else
 * (table[word9] as u64, 0x156) from arg2 (8-byte entries); then two qwords of xy pairs (16 * word, with
 * x = 16 * (word1 + arg3) + 0x7000 and y = 16 * f(word2 + arg4) + 0x7200 in the high halves, f = func_00277E68).
 * Records are read until one has word0 bit 1 set (checked after each record, starting only if bit 1 is clear).
 * Writes the trailer qwords (count | 0x8000 | 0x8400 << 48, 0x535306E1) at out and returns the next cursor. */
u8 *func_002786A0(u8 *arg0, s32 *arg1, u8 *arg2, s32 arg3, s32 arg4, f32 alpha) {
    u8 *dst = arg0;
    s32 *r;
    s32 count = 0;
    u8 *q;
    u64 tag;
    u64 ab;
    u64 cd;
    u64 regq;

    *(u64 *)dst = 0;
    *(u64 *)(dst + 8) = 0;
    dst += 16;

    if ((arg1[0] & 2) == 0) {
        r = arg1;
        for (;;) {
            if (r[0] & 1) {
                s32 alphaByte = (s32)((f32)r[13] * alpha);

                tag = (u64)(s64)r[10] | ((u64)(s64)alphaByte << 24) | ((u64)(s64)r[12] << 16) | ((u64)(s64)r[11] << 8);
                *(u64 *)(dst + 8) = 0;
                *(u64 *)dst = tag;

                q = dst + 16;
                if (r[0] & 4) {
                    *(u64 *)q = 0;
                    *(u64 *)(q + 8) = 0x46;
                } else {
                    regq = *(u64 *)(arg2 + 8 * r[9]);
                    *(u64 *)(q + 8) = 0x156;
                    *(u64 *)q = regq;
                }
                count = count + 1;

                ab = (u64)(u32)(16 * r[5]) | ((u64)(u32)(16 * r[6]) << 16);
                cd = (u64)(u32)(16 * (r[1] + arg3) + 0x7000) |
                     ((u64)(u32)(16 * func_00277E68(r[2] + arg4) + 0x7200) << 16);
                *(u64 *)(dst + 32) = ab;
                *(u64 *)(dst + 40) = cd;

                ab = (u64)(u32)(16 * r[7]) | ((u64)(u32)(16 * r[8]) << 16);
                cd = (u64)(u32)(16 * (r[3] + arg3) + 0x7000) |
                     ((u64)(u32)(16 * func_00277E68(r[4] + arg4) + 0x7200) << 16);
                *(u64 *)(dst + 48) = ab;
                *(u64 *)(dst + 56) = cd;

                dst += 64;
            }
            r += 14;
            if (r[0] & 2) {
                break;
            }
        }
    }

    *(u64 *)(arg0 + 8) = 0x535306E1u;
    *(u64 *)arg0 = (u64)(count | 0x8000) | ((u64)0x8400 << 48);
    return dst;
}
