#include "common.h"

void func_001B5DF0(void);
s32 sceVu0InversMatrix(s32 arg0, s32 arg1);
extern s32 gBtlCamView;
extern u8 *gEftShotFx;

void func_001B59D8(void) {
    sceVu0InversMatrix((s32)(gEftShotFx + 0x10), gBtlCamView);
    *(f32 *)(gEftShotFx + 0x40) = 0.0f;
    *(f32 *)(gEftShotFx + 0x48) = 0.0f;
    *(f32 *)(gEftShotFx + 0x44) = 0.0f;
    func_001B5DF0();
}
