#include "common.h"

/* 0x00129AB8: Vec4_SetZero: store four zero words at 0(dst). */
void Vec4_SetZero(f32 *dst) {
    s32 i;

    for (i = 0; i < 4; i++) {
        dst[i] = 0.0f;
    }
}
