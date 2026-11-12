#include "common.h"

s32 func_00129BD0(s32 arg0, s32 arg1, s32 arg2);  /* GUESS: asm passes a0, a1, a2 */
extern s32 gEftGlow;
extern s32 gEftGlowCfg2;

void EftGlow_GetShapePoint(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;

    temp_a2 = arg2 * 0x10;
    func_00129BD0(arg0, gEftGlow + temp_a2 + 0x20, temp_a2);
    *(f32 *)(arg0 + 0xC) = 1.0f;
    *(f32 *)(arg0 + 4) = *(f32 *)(arg0 + 4) * *(f32 *)(gEftGlowCfg2 + 8);
}
