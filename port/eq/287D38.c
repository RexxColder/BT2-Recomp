#include "common.h"

s32 rand(void);
void OldPass_MtSeedByArray(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
void OldPass_ClearBits(void);
void OldPass_PutBits(s32 arg0, s32 arg1, s32 arg2);
s32 OldPass_GetBit(s32 arg0);
s32 OldPass_MtNext(void);
void OldPass_BitsToText(s32 arg0);
extern u8 gOldPassBits[] __attribute__((section(".data")));

s32 OldPass_EncodeShort(void *arg0) {
    s32 sp[4];
    u8 *p;
    u8 *q;
    s32 seed;
    s32 r1;
    s32 s0;
    s32 s2;
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
    if (*(s32 *)(p + 8) > 0x063FFF9C) {
        *(s32 *)(p + 8) = 0x063FFF9C;
    }
    OldPass_PutBits(*(s32 *)(p + 8) / 100, 0x28, 0x14);
    OldPass_PutBits(*(s32 *)(p + 0xC), 0x3C, 2);
    OldPass_PutBits(*(s32 *)(p + 0x10), 0x3E, 1);
    OldPass_PutBits(*(s32 *)(p + 0x14), 0x3F, 4);
    OldPass_PutBits(*(s32 *)(p + 0x18), 0x43, 1);

    s2 = 0;
    s0 = 0;
    do {
        s2 += OldPass_GetBit(s0);
        s0 += 1;
    } while (s0 < 0x44);
    OldPass_PutBits(s2, 0x44, 8);

    q = gOldPassBits;
    s0 = 4;
    do {
        s0 -= 1;
        q[0xA] = (u8)(q[0] ^ q[5]);
        q += 1;
    } while (s0 >= 0);

    s0 = 4;
    do {
        mt = OldPass_MtNext();
        q = gOldPassBits + s0;
        a = *q;
        s0 += 1;
        *q = (u8)(a ^ mt);
    } while (s0 < 0xF);
    OldPass_BitsToText(0x78);
    return 1;
}
