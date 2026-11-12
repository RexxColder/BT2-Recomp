#include "common.h"

void BtlChar_SetSmallVibration(s32 arg0, f32 farg0);

/* raises the stored s32 at +0x8 of the 0x13C block to at least (int)(farg0 * 30.0f) */
void BtlChar_SetSmallVibration(s32 arg0, f32 farg0) {
    s32 *p = (s32 *)(arg0 + 0x13C);
    s32 v = (s32)(farg0 * 30.0f);
    if (p[2] < v) {
        p[2] = v;
    }
}
