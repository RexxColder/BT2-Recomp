#include "common.h"

void func_00129C28(s32 arg0, s32 arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 EftShot_HasTwoAttrs(s32 arg0, u64 arg1);
s32 EftShot_GetAttrPair(s32 arg0, u64 arg1, s32 arg2, s32 arg3);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);

/* 0x001837C8: six-step pass over the 64-byte slots of arg1 (flag word at +0, slot i at
 * +0x40*i with +0x10/+0x30 sub-blocks). Step i tests bit 2i of the flags against shot
 * attribute 2^(i+1); a two-attribute hit sets bit 2i+1 and fetches the attribute pair.
 * Step 3 only sets bit 0x40 and runs func_00129C28. Always returns 0. */
s32 func_001837C8(u8 *shot, u8 *arg1, s32 arg2)
{
    s32 tmpl[6] = {2, 4, 8, 0x10, 0x20, 0x40};
    u8 *blk;
    u8 *aux5;
    u8 *aux6;
    s32 i;
    u32 bit;
    u32 pairBit;
    u32 flags;

    for (i = 0; i < 6; i++) {
        blk = arg1 + 0x40 * i;
        aux5 = arg1 + 0x20 + 0x40 * i;
        aux6 = arg1 + 0x40 + 0x40 * i;

        if (i == 3) {
            *(u32 *)arg1 |= 0x40;
            func_00129C28((s32)(arg1 + 0xE0), arg2 + 0xAA0);
            continue;
        }

        bit = 1u << (2 * i);
        pairBit = 1u << (2 * i + 1);

        if ((*(u32 *)arg1 & bit) == 0) {
            if (EftShot_TestBits((s32)shot, tmpl[i])) {
                *(u32 *)arg1 |= bit;
                if (EftShot_HasTwoAttrs((s32)shot, tmpl[i])) {
                    *(u32 *)arg1 |= pairBit;
                    EftShot_GetAttrPair((s32)shot, tmpl[i], (s32)(blk + 0x10), (s32)(blk + 0x30));
                } else {
                    *(s32 *)(blk + 0x10) = 0;
                }
            }
        }

        flags = *(u32 *)arg1;
        if ((flags & bit) != 0) {
            func_00208DE8((s32)shot, (s32)aux5, *(s32 *)(blk + 0x10));
        } else if ((flags & 1) != 0) {
            func_00208DE8((s32)shot, (s32)aux5, *(s32 *)(arg1 + 0x10));
        }

        flags = *(u32 *)arg1;
        if ((flags & pairBit) != 0) {
            func_00208DE8((s32)shot, (s32)aux6, *(s32 *)(blk + 0x30));
        } else if ((flags & 1) != 0) {
            func_00208DE8((s32)shot, (s32)aux6, *(s32 *)(arg1 + 0x10));
        }
    }

    return 0;
}
