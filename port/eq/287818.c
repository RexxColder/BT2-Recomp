#include "common.h"

s32 OldPass_GetBit(s32 arg0);
s32 OldPass_GetBits(s32 arg0, s32 arg1);
s32 OldPass_MtNext(void);
void OldPass_MtSeedByArray(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
void OldPass_TextToBits(s32 arg0);
s32 strlen(s32 arg0);
extern u8 gOldPassBits[] __attribute__((section(".data")));

s32 OldPass_DecodeChar(s32 arg0, s32 arg1) {
    s32 sp[4];
    u8 *var_p;
    s32 temp_v0;
    s32 temp_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s1_2;

    if (strlen(arg1) != 0x20) {
        return 0;
    }
    OldPass_TextToBits(arg1);
    temp_v0 = OldPass_GetBits(0, 0x20);
    sp[0] = temp_v0;
    sp[1] = temp_v0 * 2;
    sp[2] = temp_v0 * 3;
    sp[3] = temp_v0 * 4;
    OldPass_MtSeedByArray(sp, 4, temp_v0 * 4, temp_v0 * 2);
    var_s0 = 4;
    do {
        temp_v0 = OldPass_MtNext();
        var_p = &gOldPassBits[var_s0];
        temp_a0 = *var_p;
        var_s0 += 1;
        *var_p = (u8)(temp_a0 ^ temp_v0);
    } while (var_s0 < 0x18);
    var_s1 = 0;
    var_s0 = 0;
    do {
        temp_a0 = var_s0;
        var_s0 += 1;
        var_s1 += OldPass_GetBit(temp_a0);
    } while (var_s0 < 0x77);
    if (var_s1 != OldPass_GetBits(0x77, 8)) {
        return 0;
    }
    for (var_s0 = 0; var_s0 < 8; var_s0 += 1) {
        if (gOldPassBits[var_s0 + 0x10] != (u8)(gOldPassBits[var_s0] ^ gOldPassBits[var_s0 + 8])) {
            return 0;
        }
    }
    *(s32 *)((u8 *)arg0 + 0) = OldPass_GetBits(0x20, 8);
    var_s2 = 0;
    var_s1_2 = 0x28;
    var_p = (u8 *)arg0 + 4;
    do {
        temp_a0 = var_s1_2;
        var_s1_2 += 0xA;
        var_s2 += 1;
        *(s32 *)var_p = OldPass_GetBits(temp_a0, 0xA);
        var_p += 4;
    } while (var_s2 < 7);
    *(s32 *)((u8 *)arg0 + 0x20) = OldPass_GetBits(0x6E, 3);
    *(s32 *)((u8 *)arg0 + 0x24) = OldPass_GetBits(0x71, 1);
    *(s32 *)((u8 *)arg0 + 0x28) = OldPass_GetBits(0x72, 4);
    *(s32 *)((u8 *)arg0 + 0x2C) = OldPass_GetBits(0x76, 1);
    return 1;
}
