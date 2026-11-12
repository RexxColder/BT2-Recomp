#include "common.h"

extern u8 *D_003876A0;
extern f32 D_00386EF0;

/* 0x0026A3E0: unless (D_003876A0 + 0x4D8 as s64) & 0x3800, f2 = arg0->0x1510 (set to 0.5 first when it is 0);
 * arg0->0x1510 = f2 * D_00386EF0 * (1 - f2). */
void func_0026A3E0(u8 *arg0) {
    f32 f2;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x3800) != 0) {
        return;
    }
    f2 = *(f32 *)(arg0 + 0x1510);
    if (f2 == 0.0f) {
        *(f32 *)(arg0 + 0x1510) = 0.5f;
        f2 = 0.5f;
    }
    *(f32 *)(arg0 + 0x1510) = (f2 * D_00386EF0) * (1.0f - f2);
}
