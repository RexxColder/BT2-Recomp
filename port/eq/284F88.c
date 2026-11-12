#include "common.h"

extern f32 D_003870D0;
extern f32 D_003870D4;
extern u8 *D_00387B0C;

void func_00284F88(void) {
    s32 off = 0;
    s32 i = 1;

    do {
        i -= 1;
        *(f32 *)(D_00387B0C + off + 0x8) = D_003870D0;
        *(f32 *)(D_00387B0C + off + 0xC) = D_003870D4;
        off += 0x14;
    } while (i >= 0);
}
