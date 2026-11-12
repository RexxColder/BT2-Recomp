#include "common.h"

extern void *memcpy(void *dst, const void *src, u32 n);
extern s32 rand(void);

#define SWAP32(a, b)                  \
    do {                              \
        u8 tmp_[0x20];                \
        memcpy(tmp_, (a), 0x20);      \
        memcpy((a), (b), 0x20);       \
        memcpy((b), tmp_, 0x20);      \
    } while (0)

/* 0x003D7110: shuffles the 32-byte records at G + 0x333C (count G->0x331C, with 0xD counted as 0xC), then for each
 * pair of records (2t, 2t+1) in the same table, walked with stride 0x40 from G + 0x3350 (the loop steps s0 by 2 and
 * stops when s0 >= count, so it runs (count + 1) / 2 times), swaps the two when record 2t's halfword at +0 has bit 0
 * clear and record 2t+1's has it set. Last, stores the record index as a halfword at +8 of each record. The original
 * ends with two busy-wait delay loops over the count; they have no effect and are left out. */
void func_003D7110(u8 *arg0) {
    s32 cnt;
    s32 s2;
    s32 t;
    s32 s0;
    s32 r;
    u8 *b;
    u8 *v1;

    cnt = *(s32 *)(arg0 + 0x331C);
    s2 = cnt - (cnt == 0xD ? 1 : 0);

    if (s2 > 0) {
        b = arg0 + 0x333C;
        for (t = 0; t < s2; t++) {
            r = rand() % s2;
            SWAP32(b + 0x20 * r, b + 0x20 * t);
        }

        v1 = arg0 + 0x3350;
        s0 = 0;
        do {
            s0 += 2;
            if (!(*(u16 *)(v1 - 0x14) & 1) && (*(u16 *)(v1 + 0xC) & 1)) {
                SWAP32(v1 - 0x14, v1 + 0xC);
            }
            v1 += 0x40;
        } while (s0 < s2);

        for (t = 0; t < s2; t++) {
            *(u16 *)(arg0 + 0x3344 + 0x20 * t) = (u16)t;
        }
    }
}
