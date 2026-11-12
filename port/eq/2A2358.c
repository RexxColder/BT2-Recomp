#include "common.h"

s32 memcmp(void *arg0, void *arg1, u32 arg2);
extern u8 D_00387DF8[] __attribute__((section(".data")));
extern u8 *D_00387EDC;
extern s32 D_00387ED8;
extern s32 gFontGlyphGap;

void func_002A2358(s32 arg0, u8 *arg1) {
    s32 temp_v0;
    s32 temp_v1;
    u8 *temp_a0;
    u8 *temp_v0_2;

    memcmp(arg1, D_00387DF8, 4);
    temp_v1 = *(s32 *)(arg1 + 8);
    temp_v0 = arg0 * 0x208;
    temp_a0 = arg1 + temp_v1;
    if (temp_v1 < (s32)arg1) {
        *(s32 *)(arg1 + 8) = (s32)temp_a0;
        *(s32 *)(arg1 + 0x10) = *(s32 *)(arg1 + 0x10) + (s32)arg1;
        *(s32 *)(temp_a0 + 0x38) = *(s32 *)temp_a0 + (s32)arg1;
        *(s32 *)(temp_a0 + 0x3C) = *(s32 *)(temp_a0 + 4) + (s32)arg1;
    }
    temp_v0_2 = D_00387EDC + arg0 * 0x14;
    *(s32 *)temp_v0_2 = (s32)arg1;
    *(s32 *)(temp_v0_2 + 8) = temp_v0 + 0x2A00;
    *(s32 *)(temp_v0_2 + 4) = temp_v0 + 0x2A08;
    *(s32 *)(temp_v0_2 + 0xC) = *(s32 *)(arg1 + 0x18);
    *(s32 *)(temp_v0_2 + 0x10) = *(s32 *)(arg1 + 0x1C);
    gFontGlyphGap = 0;
    D_00387ED8 = *(s32 *)(arg1 + 0x1C);
}
