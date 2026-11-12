#include "common.h"

typedef s32 (*CbFn)(void);
u8 *func_0010B078(void);
void EftShotFx_Update(s32 arg0);
void func_00113598(u8 *arg0);
void HudGfx_SetEnv(void);
void HudGfx_ClearAlpha(void);
extern u8 *D_003876A0;
extern u8 *D_003876C8;
extern u8 D_003876D0[];
extern void *memcpy(void *dst, const void *src, u32 n);

/* 0x0010AF08: s0 = func_0010B078(); 8 bytes of D_003876D0 copied to a frame; unless state (D_003876A0+0xB8) == 6:
 * two words in the D_003876C8 block set, EftShotFx_Update(1), func_00113598(frame), HudGfx_SetEnv, HudGfx_ClearAlpha,
 * then four no-argument callbacks at s0+0x1354/0x1350/0x135C/0x1360 run in turn; a callback that returns nonzero
 * clears its own slot. */
void func_0010AF08(void) {
    u8 *s0;
    u8 frame[8];

    s0 = func_0010B078();
    memcpy(frame, D_003876D0, 8);
    if (*(s32 *)(D_003876A0 + 0xB8) == 6) {
        return;
    }
    *(s32 *)(D_003876C8 + 0x91F0) = 0;
    *(s32 *)(D_003876C8 + 0x91F4) = 1;
    EftShotFx_Update(1);
    func_00113598(frame);
    HudGfx_SetEnv();
    HudGfx_ClearAlpha();
    if (*(s32 *)(s0 + 0x1354) != 0) {
        if (((CbFn)(*(s32 *)(s0 + 0x1354)))() != 0) {
            *(s32 *)(s0 + 0x1354) = 0;
        }
    }
    if (*(s32 *)(s0 + 0x1350) != 0) {
        if (((CbFn)(*(s32 *)(s0 + 0x1350)))() != 0) {
            *(s32 *)(s0 + 0x1350) = 0;
        }
    }
    if (*(s32 *)(s0 + 0x135C) != 0) {
        if (((CbFn)(*(s32 *)(s0 + 0x135C)))() != 0) {
            *(s32 *)(s0 + 0x135C) = 0;
        }
    }
    if (*(s32 *)(s0 + 0x1360) != 0) {
        if (((CbFn)(*(s32 *)(s0 + 0x1360)))() != 0) {
            *(s32 *)(s0 + 0x1360) = 0;
        }
    }
}
