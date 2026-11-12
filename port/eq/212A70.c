#include "common.h"

void BtlChar_SetSmallVibration(u8 *arg0, f32 arg1) {
    u8 *p = arg0 + 0x13C;
    s32 v = (s32)(arg1 * 30.0f);

    if (*(s32 *)(p + 8) < v) {
        *(s32 *)(p + 8) = v;
    }
}
