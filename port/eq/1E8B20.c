#include "common.h"

s32 func_00126460(s32 arg0);
void EftTexSet_Load8(s32 arg0, s32 arg1);
void EftTexSet_Load16(s32 arg0, s32 arg1);
void EftTexSet_Load32(s32 arg0, s32 arg1);
extern u8 *D_003878F4;

void func_001E8B20(void) {
    u8 *s0;
    u8 *s1;
    s32 r;

    s0 = D_003878F4;
    *(s32 *)(s0 + 0x210) = func_00126460(0x5C);
    s1 = s0 + 0x218;
    r = func_00126460(0x3E);
    *(s32 *)(s1 + 0x00) = r;
    EftTexSet_Load8((s32)(s0 + 0x220), r);

    r = func_00126460(0x58);
    *(s32 *)(s1 + 0x98) = r;
    r = func_00126460(0x59);
    *(s32 *)(s1 + 0x9C) = r;
    r = func_00126460(0x55);
    *(s32 *)(s1 + 0x1C0) = r;
    EftTexSet_Load16((s32)(s0 + 0x3E0), r);

    r = func_00126460(0x56);
    *(s32 *)(s1 + 0x2D8) = r;
    r = func_00126460(0x57);
    *(s32 *)(s1 + 0x2DC) = r;
    r = func_00126460(0x4E);
    *(s32 *)(s0 + 0x4F8) = r;
    EftTexSet_Load32((s32)(s0 + 0x500), r);

    r = func_00126460(0x5A);
    *(s32 *)(s0 + 0x928) = r;
    r = func_00126460(0x50);
    *(s32 *)(s0 + 0x710) = r;
    EftTexSet_Load32((s32)(s0 + 0x718), r);

    r = func_00126460(0x5B);
    *(s32 *)(s0 + 0x92C) = r;
    r = func_00126460(0x38);
    *(s32 *)(s1 + 0x720) = r;
    EftTexSet_Load16((s32)(s0 + 0x940), r);

    r = func_00126460(0x53);
    *(s32 *)(s1 + 0x838) = r;
    r = func_00126460(0x54);
    *(s32 *)(s1 + 0x83C) = r;
}
