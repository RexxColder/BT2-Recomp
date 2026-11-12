#include "common.h"
extern s32 D_003876A4;
void *memset(void *s, s32 c, u32 n);

void func_00102360(void) {
    u8 *g;
    s32 k;

    if (D_003876A4 == 0) {
        return;
    }
    g = (u8 *)D_003876A4;
    *(s32 *)(g + 0x28) = 0;
    memset(g + 0x2C, 0, 0x14);
    memset(g + 0x40, 0, 0x48);
    memset(g + 0x88, 0, 0x308);
    memset(g + 0x390, 0, 0xE8);
    memset(g + 0x478, 0, 0x14);
    memset(g + 0x48C, 0, 0x28);
    memset(g + 0x4B4, 0, 0xC);
    *(s32 *)(g + 0x4C0) = 0;
    *(s32 *)(g + 0x4C4) = 0;
    for (k = 0; k < 5; k++) {
        *(s32 *)(g + 0x390 + 4 * k) = 0;
        *(s32 *)(g + 0x3A4 + 4 * k) = 1;
    }
}
