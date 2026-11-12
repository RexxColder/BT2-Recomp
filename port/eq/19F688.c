#include "common.h"

extern u8 *D_003877F8;
extern s32 D_003422D0[];

s32 func_00126460(s32 arg0);
s32 func_001C1D68(s32 arg0);

void func_0019F688(void) {
    s32 r1;
    s32 r2;
    s32 r3;
    s32 i;
    s32 v;
    u8 *src;
    u8 *dst;

    r1 = func_00126460(0x5D);
    r2 = func_001C1D68(r1);
    *(s32 *)D_003877F8 = r2;
    r3 = func_00126460(0x98);
    src = (u8 *)r3;
    dst = D_003877F8 + 4;
    for (i = 0; i < 0x1B9; i++) {
        dst[i] = src[i];
    }
    for (i = 0; i < 13; i++) {
        v = func_00126460(D_003422D0[i]);
        *(s32 *)(D_003877F8 + 4 * i + 0x1C0) = v;
    }
}
