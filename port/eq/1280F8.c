#include "common.h"

extern void EftHit_SetRadiusA(s32 arg0, f32 radius);
extern void EftHit_SetRadiusB(s32 arg0, f32 radius);

f32 func_001280F8(u8 *self) {
    u8 *child = *(u8 **)(self + 0x64);

    if (child != 0 && **(s32 **)(child + 0x20) == 0x153) {
        EftHit_SetRadiusA((s32)self, 9.0f);
        EftHit_SetRadiusB((s32)self, 9.0f);
    }
    return 0.0f;
}
