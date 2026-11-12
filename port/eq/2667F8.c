#include "common.h"

extern u8 *D_003876A0;
extern f32 D_00386EB4;

/* 0x002667F8: unless the 64-bit flags at D_003876A0 + 0x4D8 have bit 0x100 set, arg0->0xE58 -= D_00386EB4 and it
 * is clamped to 0.0 when that goes negative. */
void func_002667F8(u8 *arg0) {
    f32 f0;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }
    f0 = *(f32 *)(arg0 + 0xE58) - D_00386EB4;
    *(f32 *)(arg0 + 0xE58) = f0;
    if (f0 < 0.0f) {
        *(f32 *)(arg0 + 0xE58) = 0.0f;
    }
}
