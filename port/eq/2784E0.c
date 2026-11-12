#include "m2c_macros.h"

s32 func_00277E68(s32 arg0);

/* GS packet for a list of 0x38-byte strip records (flags at +0: bit 0 = draw, bit 2 = no tag quad, bit 1 ends
 * the list). Each drawn record adds four quads at the cursor: a packed colour, a tag (table entry or 0x156),
 * and two vertices (positions scaled by 16 with the offsets 0x7000/0x7200 and func_00277E68 on the
 * depth). The header quad (count | 0x8000, GIF tag) is written at the start. Returns the cursor. */
u8 *GsPkt_EmitStrips(u8 *arg0, u8 *arg1, u64 *arg2) {
    u8 *s1;
    u8 *s0;
    s32 s2;
    s32 r;
    s64 packed;

    s1 = arg0;
    *(u64 *)(s1 + 0x0) = 0;
    *(u64 *)(s1 + 0x8) = 0;
    s1 += 0x10;
    s2 = 0;

    if ((*(u32 *)arg1 & 2) == 0) {
        s0 = arg1;
        do {
            if ((*(u32 *)s0 & 1) != 0) {
                packed = (s64)*(s32 *)(s0 + 0x28)
                    | ((s64)*(s32 *)(s0 + 0x34) << 24)
                    | ((s64)*(s32 *)(s0 + 0x30) << 16)
                    | ((s64)*(s32 *)(s0 + 0x2C) << 8);
                *(u64 *)(s1 + 0x8) = 0;
                *(u64 *)(s1 + 0x0) = packed;

                s1 += 0x10;
                if ((*(u32 *)s0 & 4) != 0) {
                    *(u64 *)(s1 + 0x0) = 0;
                    *(u64 *)(s1 + 0x8) = 0x46;
                } else {
                    *(u64 *)(s1 + 0x0) = arg2[*(s32 *)(s0 + 0x24)];
                    *(u64 *)(s1 + 0x8) = 0x156;
                }

                s1 += 0x10;
                *(u64 *)(s1 + 0x0) = (s64)(s32)(*(s32 *)(s0 + 0x14) * 16)
                    | ((s64)(s32)(*(s32 *)(s0 + 0x18) * 16) << 16);
                r = func_00277E68(*(s32 *)(s0 + 0x8));
                *(u64 *)(s1 + 0x8) = (s64)(s32)(*(s32 *)(s0 + 0x4) * 16 + 0x7000)
                    | ((s64)(s32)(r * 16 + 0x7200) << 16);

                s1 += 0x10;
                *(u64 *)(s1 + 0x0) = (s64)(s32)(*(s32 *)(s0 + 0x1C) * 16)
                    | ((s64)(s32)(*(s32 *)(s0 + 0x20) * 16) << 16);
                r = func_00277E68(*(s32 *)(s0 + 0x10));
                *(u64 *)(s1 + 0x8) = (s64)(s32)(*(s32 *)(s0 + 0xC) * 16 + 0x7000)
                    | ((s64)(s32)(r * 16 + 0x7200) << 16);

                s1 += 0x10;
                s2 += 1;
            }
            s0 += 0x38;
        } while ((*(u32 *)s0 & 2) == 0);
    }

    *(u64 *)(arg0 + 0x8) = 0x535306E1ULL;
    *(u64 *)(arg0 + 0x0) = (u64)(s64)(s2 | 0x8000) | 0x8400000000000000ULL;
    return s1;
}
