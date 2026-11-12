#include "common.h"

extern void *D_003879D0;
extern s32 D_00387F2C;

s32 func_002492E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0024B010(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4);
s32 func_0024B210(u8 *arg0);

void func_002541B0(void) {
    u8 sp[0x20];
    u8 *g;
    u8 *c;
    s32 k;
    s32 j;
    s32 temp_a0;
    s32 r;
    s32 t1;

    g = (u8 *)D_003879D0;
    j = *(s32 *)(g + 0x160);
    temp_a0 = *(s32 *)(g + j * 8 + 0x174);
    k = *(s32 *)(g + 0x168);
    *(s32 *)(g + k * 20 + 0x1A0) = temp_a0;
    j = *(s32 *)(g + 0x160);
    *(s32 *)(g + k * 20 + 0x1AC) = *(s32 *)(*(u8 **)(g + 0x2A4) + j * 16 + 0xC);
    c = g + 0xC;
    j = *(s32 *)(g + 0x160);
    k = *(s32 *)(g + 0x168);
    *(s32 *)(c + 0x70 + (0x12 - k) * 4) = *(s32 *)(c + j * 4 + 0x10C);
    r = func_002492E0(temp_a0, *(s32 *)(g + 0x280), *(s32 *)(g + 0x284), 1);
    k = *(s32 *)(g + 0x168);
    *(s32 *)(g + k * 20 + 0x1A8) = r;
    k = *(s32 *)(g + 0x168);
    t1 = *(s32 *)(g + k * 20 + 0x1A8);
    func_0024B010(*(s32 *)(g + 0x288), *(s32 *)(g + 0x28C),
                  D_00387F2C + t1 * 34 + 0x1408, sp, 0x14);
    k = *(s32 *)(g + 0x168);
    *(s32 *)(g + k * 20 + 0x1A4) = func_0024B210(sp);
}
