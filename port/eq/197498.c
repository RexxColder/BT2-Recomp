#include "common.h"

extern s32 gEftGlow;
s32 func_00129C28(s32 arg0, s32 arg1, s32 arg2, f32 farg0);

void EftGlow_GetShapeDir(u8 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    s32 p = gEftGlow + (arg2 << 4) + 0x160;

    func_00129C28((s32)arg0, p, arg2 << 4, farg0);
    *(f32 *)(arg0 + 4) = *(f32 *)(arg0 + 4) * farg0;
}
