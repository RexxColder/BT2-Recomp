/*
 * Fighter pad queries, 0x207BF0..0x207D40. BT2's fighter keeps three button words at +0x48 / +0x4C / +0x50, a
 * table of 32 key masks at +0x58 (one per battle key) and three tables of 32 per-bit frame counters (bytes) at
 * +0xDC, +0xFC and +0x11C. A key is looked up through its mask; a counter through the bit number of the mask
 * (func_00207260 counts how often the mask can be halved). The meaning of the three words / counters is inferred
 * from the calls in the action code (0x229D6C etc.), not verified.
 */
#include "common.h"

typedef struct BtlPadChr {
    /* 0x000 */ u8 unk0[0x48];
    /* 0x048 */ u32 bits48;
    /* 0x04C */ u32 bits4C;
    /* 0x050 */ u32 bits50;
    /* 0x054 */ u8 unk54[4];
    /* 0x058 */ u32 mask[32];
    /* 0x0D8 */ u8 unkD8[4];
    /* 0x0DC */ s8 countDC[32];
    /* 0x0FC */ s8 countFC[32];
    /* 0x11C */ s8 count11C[32];
} BtlPadChr;

extern s32 func_00207260(u32 mask); /* bit number of a one-bit mask */

/* bits & mask[key]. */
u32 BtlPad_TestMask(s32 key, u32 bits, u32 *mask) {
    return bits & mask[key];
}

/* Key `key` in button word +0x4C. */
u32 BtlPad_Test4C(BtlPadChr *chr, s32 key) {
    return BtlPad_TestMask(key, chr->bits4C, chr->mask);
}

/* Key `key` in button word +0x48. */
u32 BtlPad_Test48(BtlPadChr *chr, s32 key) {
    return BtlPad_TestMask(key, chr->bits48, chr->mask);
}

/* Key `key` in button word +0x50. */
u32 BtlPad_Test50(BtlPadChr *chr, s32 key) {
    return BtlPad_TestMask(key, chr->bits50, chr->mask);
}

/* Mask of key `key`. */
u32 BtlPad_GetMask(BtlPadChr *chr, s32 key) {
    return chr->mask[key];
}

/* Counter of key `key` in a table of 32 per-bit counters. */
s32 BtlPad_GetCount(s32 key, s8 *count, u32 *mask) {
    return count[func_00207260(mask[key])];
}

/* Counter +0xDC of key `key`. */
s32 BtlPad_GetCountDC(BtlPadChr *chr, s32 key) {
    return BtlPad_GetCount(key, chr->countDC, chr->mask);
}

/* Counter +0xFC of key `key`. */
s32 BtlPad_GetCountFC(BtlPadChr *chr, s32 key) {
    return BtlPad_GetCount(key, chr->countFC, chr->mask);
}

/* Counter +0x11C of key `key`. */
s32 BtlPad_GetCount11C(BtlPadChr *chr, s32 key) {
    return BtlPad_GetCount(key, chr->count11C, chr->mask);
}
