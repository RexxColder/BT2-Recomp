#include "common.h"

extern f32 D_00385A40;
extern u8 *D_003876A0;
extern u8 *D_00387930;

s32 func_00212900(void) {
    u8 *p;
    f32 temp_f2;

    if (((*(s64 *)(D_003876A0 + 0x4D8)) & 0x3800) != 0) {
        return 0;
    }
    p = D_00387930;
    if (*(f32 *)(p + 0x10) == 0.0f) {
        *(f32 *)(p + 0x10) = 0.5f;
    }
    temp_f2 = *(f32 *)(p + 0x10);
    *(f32 *)(p + 0x10) = temp_f2 * D_00385A40 * (1.0f - temp_f2);
    return *(s32 *)(p + 0x10);
}
