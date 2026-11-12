#include "common.h"

s32 OldPass_GetBit(s32 arg0);
s32 OldPass_GetBits(s32 arg0, s32 arg1);
s32 OldPass_MtNext(void);
void OldPass_MtSeedByArray(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
void OldPass_TextToBits(void *arg0);
s32 strlen(void *arg0);
extern u8 gOldPassBits[] __attribute__((section(".data")));

s32 OldPass_DecodeShort(void *arg0, void *arg1) {
    s32 sp[4];
    s32 s0;
    s32 s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 mt;
    s32 i;
    u8 a;
    u8 *p;
    u8 *out;

    out = (u8 *)arg0;
    if (strlen(arg1) != 0x14) {
        return 0;
    }
    OldPass_TextToBits(arg1);
    temp_v0 = OldPass_GetBits(0, 0x20);
    sp[0] = temp_v0;
    sp[1] = temp_v0 * 2;
    sp[2] = temp_v0 * 3;
    sp[3] = temp_v0 * 4;
    OldPass_MtSeedByArray(sp, 4, temp_v0 * 4, temp_v0 * 2);

    s0 = 4;
    do {
        mt = OldPass_MtNext();
        p = gOldPassBits + s0;
        a = *p;
        s0 += 1;
        *p = (u8)(a ^ mt);
    } while (s0 < 0xF);

    s1 = 0;
    s0 = 0;
    do {
        s1 += OldPass_GetBit(s0);
        s0 += 1;
    } while (s0 < 0x44);

    if (s1 != OldPass_GetBits(0x44, 8)) {
        return 0;
    }

    for (i = 0; i < 5; i++) {
        p = gOldPassBits + i;
        if (p[0xA] != (p[0] ^ p[5])) {
            return 0;
        }
    }

    temp_v0_2 = OldPass_GetBits(0x20, 8);
    *(s32 *)(out + 4) = 0;
    *(s32 *)(out + 0) = temp_v0_2;
    *(s32 *)(out + 8) = OldPass_GetBits(0x28, 0x14) * 0x64;
    *(s32 *)(out + 0xC) = OldPass_GetBits(0x3C, 2);
    *(s32 *)(out + 0x10) = OldPass_GetBits(0x3E, 1);
    *(s32 *)(out + 0x14) = OldPass_GetBits(0x3F, 4);
    *(s32 *)(out + 0x18) = OldPass_GetBits(0x43, 1);
    return 1;
}
