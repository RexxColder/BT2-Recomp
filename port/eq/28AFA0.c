#include "common.h"

/* 0x0028AFA0: D_00387EB0 = 0; D_00387EB1 = 0; arr[0] = f(0x100000); arr[1] = f(0x100000);
   arr[2] = f(0x400); arr[3] = f(0x400); gDmaCur = arr[D_00387EB0]. arr = D_0038A628. */
extern u8 D_0038A628[];
extern u8 D_00387EB0;
extern u8 D_00387EB1;
extern s32 D_00387EAC;
s32 func_0028BAA8(s32 arg0);

void func_0028AFA0(void) {
    s32 idx;

    D_00387EB0 = 0;
    D_00387EB1 = 0;
    *(s32 *)(D_0038A628 + 0x0) = func_0028BAA8(0x100000);
    *(s32 *)(D_0038A628 + 0x4) = func_0028BAA8(0x100000);
    *(s32 *)(D_0038A628 + 0x8) = func_0028BAA8(0x400);
    *(s32 *)(D_0038A628 + 0xC) = func_0028BAA8(0x400);
    idx = D_00387EB0;
    D_00387EAC = *(s32 *)(D_0038A628 + (idx << 2));
}
