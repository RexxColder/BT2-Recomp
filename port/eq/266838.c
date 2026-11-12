#include "common.h"

extern u8 *D_003876A0;
extern f32 D_00386EB8;
extern f32 D_00386EBC;

/* 0x00266838(obj): returns 0. Does nothing when the 64-bit word at D_003876A0 + 0x4D8 has bit 8 set. The float at
 * obj+0xFC0 moves: when obj->0xAF0 has bit 18 set it gets + D_00386EB8, clamped to 1.0f from above; otherwise it
 * gets - D_00386EBC, clamped to 0.0f from below. */
s32 func_00266838(u8 *arg0) {
    f32 *p = (f32 *)(arg0 + 0xFC0);
    f32 f;

    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0xAF0) & 0x40000) {
        f = *p + D_00386EB8;
        *p = f;
        if (1.0f < f) {
            *p = 1.0f;
        }
    } else {
        f = *p - D_00386EBC;
        *p = f;
        if (f < 0.0f) {
            *p = 0.0f;
        }
    }
    return 0;
}
