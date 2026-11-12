#include "common.h"

s32 func_00126460(s32 arg0);
s32 func_00126560(void);
s32 EftTexSet_Load32(s32 arg0, s32 arg1);
void EftTexSet_Load8(s32 arg0, s32 arg1);
s32 EftTexSet_Load16(s32 arg0, s32 arg1);
extern u8 *gEftStruggle;

void func_001A8280(void) {
    u8 *s1;
    u8 *s0;
    s32 v;
    s32 id;

    s1 = gEftStruggle;
    *(s32 *)(s1 + 0x8) = func_00126460(0xF5);
    s0 = s1 + 0x10;
    v = func_00126460(0x3E);
    *(s32 *)(s1 + 0x10) = v;
    EftTexSet_Load8((s32)(s1 + 0x18), v);
    *(s32 *)(s0 + 0x98) = func_00126460(0xFC);
    *(s32 *)(s0 + 0x9C) = func_00126460(0xFD);
    v = func_00126460(0xF9);
    *(s32 *)(s0 + 0xA0) = v;
    EftTexSet_Load16((s32)(s1 + 0xB8), v);
    *(s32 *)(s0 + 0x1B8) = func_00126460(0xFA);
    *(s32 *)(s0 + 0x1BC) = func_00126460(0xFB);
    if (func_00126560() != 0) {
        v = func_00126460(0xB);
        *(s32 *)(s0 + 0x1C0) = v;
        EftTexSet_Load32((s32)(s1 + 0x1D8), v);
        id = 0x15;
    } else {
        v = func_00126460(0x101);
        *(s32 *)(s0 + 0x1C0) = v;
        EftTexSet_Load32((s32)(s1 + 0x1D8), v);
        id = 0x102;
    }
    *(s32 *)(s0 + 0x3D8) = func_00126460(id);
    v = func_00126460(0xF6);
    *(s32 *)(s0 + 0x3E0) = v;
    EftTexSet_Load16((s32)(s0 + 0x3E8), v);
    *(s32 *)(s0 + 0x4F8) = func_00126460(0xF7);
    *(s32 *)(s0 + 0x4FC) = func_00126460(0xF8);
    v = func_00126460(0xFE);
    *(s32 *)(s0 + 0x500) = v;
    EftTexSet_Load16((s32)(s0 + 0x508), v);
    *(s32 *)(s0 + 0x618) = func_00126460(0xFF);
    *(s32 *)(s0 + 0x61C) = func_00126460(0x100);
}
