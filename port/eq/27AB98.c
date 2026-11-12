#include "common.h"

/* 0x0027AB98: p = D_003876A0; if ((*(s64 *)(p + 0x4D8) & 3) == 0) return; g = D_00387AE8;
   if (g->+0x54 (u8) != 1) return; func_0027A970(a0); a0->+0x54 = 0. */
extern u8 D_003876A0[];
extern u8 D_00387AE8[];
void func_0027A970();

void func_0027AB98(s32 a0) {
    u8 *p;
    u8 *g;

    p = *(u8 **)D_003876A0;
    if ((*(s64 *)(p + 0x4D8) & 3) == 0) {
        return;
    }
    g = *(u8 **)D_00387AE8;
    if (*(u8 *)(g + 0x54) != 1) {
        return;
    }
    func_0027A970(a0);
    *(u8 *)((u8 *)a0 + 0x54) = 0;
}
