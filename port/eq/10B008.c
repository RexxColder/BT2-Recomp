#include "common.h"

extern void *memset(void *dst, s32 c, u32 n);
void EftShotFx_Update();
void func_00113598(s32 arg0);
void HudGfx_SetEnv();
void HudGfx_ClearAlpha();
void func_00111170();

/* 0x0010B008: clears an 8-byte buffer, then EftShotFx_Update(), func_00113598(buf), HudGfx_SetEnv(),
 * HudGfx_ClearAlpha(), func_00111170(). The later calls get no arguments from the asm. */
void func_0010B008(void) {
    s32 buf[2];

    memset(buf, 0, 8);
    EftShotFx_Update();
    func_00113598((s32)buf);
    HudGfx_SetEnv();
    HudGfx_ClearAlpha();
    func_00111170();
}
