#include "common.h"

f32 Mathf_Asin(f32 x);
f32 atan2f(f32 y, f32 x);
extern f32 D_003872A8;
extern f32 D_003872AC;

void Mtx_ToEuler(u8 *arg0, u8 *arg1) {
    f32 m24;
    f32 t;

    *(f32 *)(arg0 + 0) = Mathf_Asin(*(f32 *)(arg1 + 0x24));
    m24 = *(f32 *)(arg1 + 0x24);
    if (!(m24 < D_003872A8)) {
        t = atan2f(*(f32 *)(arg1 + 0x10), *(f32 *)(arg1 + 0));
        *(f32 *)(arg0 + 4) = t;
        *(s32 *)(arg0 + 8) = 0;
    } else if (D_003872AC < m24) {
        *(f32 *)(arg0 + 4) = atan2f(*(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x28));
        *(f32 *)(arg0 + 8) = atan2f(-*(f32 *)(arg1 + 4), *(f32 *)(arg1 + 0x14));
    } else {
        t = atan2f(*(f32 *)(arg1 + 0x10), *(f32 *)(arg1 + 0));
        *(s32 *)(arg0 + 8) = 0;
        *(f32 *)(arg0 + 4) = -t;
    }
    *(s32 *)(arg0 + 0xC) = 0;
}
