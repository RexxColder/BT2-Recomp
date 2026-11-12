#include "common.h"

s32 rand(void);
void OldPass_MtSeedByArray(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
void OldPass_ClearBits(void);
void OldPass_PutBits(s32 arg0, s32 arg1, s32 arg2);
s32 OldPass_GetBit(s32 arg0);
s32 OldPass_MtNext(void);
void OldPass_BitsToText(s32 arg0);
extern u8 gOldPassBits[] __attribute__((section(".data")));

s32 OldPass_EncodeChar(void *arg0) {
    s32 sp[4];
    u8 *p;
    u8 *q;
    s32 seed;
    s32 r1;
    s32 s0;
    s32 s1v;
    s32 k;
    s32 mt;
    u8 a;

    p = (u8 *)arg0;
    r1 = rand();
    seed = (s32)(((u32)r1 << 16) | ((u32)rand() & 0xFFFF));
    sp[0] = seed;
    sp[1] = seed * 2;
    sp[2] = seed * 3;
    sp[3] = seed * 4;
    OldPass_MtSeedByArray(sp, 4, seed * 2, 0);
    OldPass_ClearBits();
    OldPass_PutBits(seed, 0, 0x20);
    OldPass_PutBits(*(s32 *)(p + 0), 0x20, 8);
    for (k = 0; k < 7; k++) {
        OldPass_PutBits(*(s32 *)(p + 4 + 4 * k), 0x28 + 10 * k, 0xA);
    }
    OldPass_PutBits(*(s32 *)(p + 0x20), 0x6E, 3);
    OldPass_PutBits(*(s32 *)(p + 0x24), 0x71, 1);
    OldPass_PutBits(*(s32 *)(p + 0x28), 0x72, 4);
    OldPass_PutBits(*(s32 *)(p + 0x2C), 0x76, 1);

    s1v = 0;
    s0 = 0;
    do {
        s1v += OldPass_GetBit(s0);
        s0 += 1;
    } while (s0 < 0x80);
    OldPass_PutBits(s1v, 0x77, 8);

    q = gOldPassBits;
    s0 = 7;
    do {
        s0 -= 1;
        q[0x10] = (u8)(q[0] ^ q[8]);
        q += 1;
    } while (s0 >= 0);

    s0 = 4;
    do {
        mt = OldPass_MtNext();
        q = gOldPassBits + s0;
        a = *q;
        s0 += 1;
        *q = (u8)(a ^ mt);
    } while (s0 < 0x18);
    OldPass_BitsToText(0xC0);
    return 1;
}
