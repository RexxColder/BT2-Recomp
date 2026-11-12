#include "common.h"

extern u8 *D_003876A0;
extern u8 *gEftStageScroll;

void func_00130D38(void) {
    u8 *g;
    s64 v;
    f32 f1;
    f32 f2;

    v = *(s64 *)(D_003876A0 + 0x4D8);
    if (v & 0x100) {
        return;
    }
    if (v & 0x2000) {
        return;
    }
    g = gEftStageScroll;
    if (*(u8 *)(g + 0x2B0) == 0) {
        return;
    }
    *(f32 *)(g + 0x298) = *(f32 *)(g + 0x298) + *(f32 *)(g + 0x290) * *(f32 *)(g + 0x2A0);
    *(f32 *)(g + 0x29C) = *(f32 *)(g + 0x29C) + *(f32 *)(g + 0x294) * *(f32 *)(g + 0x2A0);

    f2 = *(f32 *)(g + 0x298);
    f1 = *(f32 *)(g + 0x2A4);
    if (f1 < f2) {
        *(f32 *)(g + 0x298) = f2 - f1;
    } else if (f2 < -f1) {
        *(f32 *)(g + 0x298) = f2 + f1;
    }

    f2 = *(f32 *)(g + 0x29C);
    f1 = *(f32 *)(g + 0x2A4);
    if (f1 < f2) {
        *(f32 *)(g + 0x29C) = f2 - f1;
    } else if (f2 < -f1) {
        *(f32 *)(g + 0x29C) = f2 + f1;
    }
}
