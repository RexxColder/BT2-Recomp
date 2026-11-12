#include "m2c_macros.h"

void ColBox_GetSize(void *arg0, void *arg1) {
    u8 *src = (u8 *)arg0;
    u8 *dst = (u8 *)arg1;

    *(f32 *)(dst + 0) = *(f32 *)(src + 0xC) - *(f32 *)(src + 0x0);
    *(f32 *)(dst + 4) = *(f32 *)(src + 0x10) - *(f32 *)(src + 0x4);
    *(f32 *)(dst + 0xC) = 1.0f;
    *(f32 *)(dst + 8) = *(f32 *)(src + 0x14) - *(f32 *)(src + 0x8);
}
