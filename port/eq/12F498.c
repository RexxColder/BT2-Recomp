#include "common.h"

s32 EftStage_IsDrawOn(void);
void func_00130678(s32 arg0);
void sceVu0InversMatrix(void *arg0, s32 arg1);
extern s32 gBtlCamView;
extern u8 *gEftBubble;

void func_0012F498(void) {
    if (EftStage_IsDrawOn() != 0) {
        sceVu0InversMatrix(gEftBubble + 0x20, gBtlCamView);
        *(f32 *)(gEftBubble + 0x50) = 0.0f;
        *(f32 *)(gEftBubble + 0x58) = 0.0f;
        *(f32 *)(gEftBubble + 0x54) = 0.0f;
        func_00130678(*(s32 *)(gEftBubble + 0x8));
    }
}
