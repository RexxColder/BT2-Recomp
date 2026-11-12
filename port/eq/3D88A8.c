#include "common.h"

extern u8 *D_004263E8 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));

/* 0x003D88A8: S = D_004263E8; n = S->0x6E20 (< 0 or 0 entries: -1); B = S->0x6E1C (NULL: -1). Walks the 12-byte
 * records at B (n of them) looking for a record whose (word0, word1) is (arg0, arg1) or (arg1, arg0). On a hit with
 * idx = rec->word2: returns idx when (s16) D_387F2C[idx] (at +0x1F32, 4-byte stride) < the word at S->0x14 + 48*idx + 0x10,
 * else -1. No hit: -1. */
s32 func_003D88A8(s32 arg0, s32 arg1) {
    u8 *s;
    s32 n;
    u8 *rec;
    s32 i;

    s = D_004263E8;
    n = *(s32 *)(s + 0x6E20);
    if (n < 0) {
        return -1;
    }
    rec = *(u8 **)(s + 0x6E1C);
    if (rec == NULL) {
        return -1;
    }
    if (n <= 0) {
        return -1;
    }

    i = 0;
    do {
        s32 k0 = *(s32 *)(rec + 0);
        s32 k1 = *(s32 *)(rec + 4);

        if ((k0 == arg0 && k1 == arg1) || (k0 == arg1 && k1 == arg0)) {
            s32 idx = *(s32 *)(rec + 8);
            u8 *tb = D_387F2C;
            u8 *c2 = *(u8 **)(s + 0x14);
            s16 h = *(s16 *)(tb + idx * 4 + 0x1F32);
            s32 v = *(s32 *)(c2 + idx * 48 + 0x10);

            if (h < v) {
                return idx;
            }
            return -1;
        }
        i++;
        rec += 0xC;
    } while (i < n);

    return -1;
}
