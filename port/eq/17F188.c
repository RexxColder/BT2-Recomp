#include "common.h"

extern u8 *gEftBoltPool;

void func_001F0EE8(u32 a0, u32 a1, u32 a2, u32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   s32 st0, u32 st1, s32 st2, s32 st3, void *st4);

/* 0x0017F188 (EftBolt_DrawFlashes, BT3 name): draws the 20 flash sprites of the work block
 * (records of 0x70 at +0x5B0). Colours and alpha are scaled by 255, size by 4096. */
void EftBolt_DrawFlashes(u8 *arg0, f32 farg0) {
    u8 *rec;
    u8 *tex;
    s32 i;
    u32 r;
    u32 g;
    u32 b;
    u32 a;
    u32 sz;

    tex = gEftBoltPool + 0x268;
    rec = arg0 + 0x5B0;
    for (i = 19; i >= 0; i--, rec += 0x70) {
        if ((*(s32 *)rec & 1) == 0) {
            continue;
        }
        r = (u32)(*(f32 *)(rec + 0x50) * 255.0f) & 0xFF;
        g = (u32)(*(f32 *)(rec + 0x54) * 255.0f) & 0xFF;
        b = (u32)(*(f32 *)(rec + 0x58) * 255.0f) & 0xFF;
        a = (u32)(*(f32 *)(rec + 0x5C) * 255.0f * farg0) & 0xFF;
        sz = (u32)(*(f32 *)(rec + 0x18) * 4096.0f);
        func_001F0EE8(r, g, b, a, 0, 0, 0x40, 0x40,
                      *(f32 *)(rec + 0x30), *(f32 *)(rec + 0x34), *(f32 *)(rec + 0x38),
                      *(f32 *)(rec + 0x60), *(f32 *)(rec + 0x64), *(f32 *)(rec + 0x68),
                      *(f32 *)(rec + 0x6C), *(f32 *)(rec + 0x28),
                      0, sz, 0, 1, tex + *(s32 *)(rec + 0x10) * 16);
    }
}
