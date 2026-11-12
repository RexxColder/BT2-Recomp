#include "common.h"

s32 EftStage_IsDrawOn(s32 arg0);
void Vu0Screen_StoreMtx(s32 arg0);
void func_00128EF0(void);
void func_00128F90(s32 arg0);
void Mtx_InverseRT(s32 arg0, s32 arg1);
void EftWaterSplash_DrawList(s32 arg0);
void EftWaterTrail_DrawList(s32 arg0);
void EftWaterRing_DrawList(s32 arg0);
void EftWaterSpray_DrawList(s32 arg0, s32 arg1);
void EftWaterDrop_DrawList(s32 arg0, s32 arg1);
void func_001404A0(s32 arg0);
void func_00128F08(void);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern s32 gBtlCamView;
extern u8 *gEftDust;

void func_0013C7C8(s32 arg0) {
    s32 sp[16];

    if (EftStage_IsDrawOn(arg0) != 0) {
        Vu0Screen_StoreMtx((s32)sp);
        func_00128EF0();
        func_00128F90((s32)sp);
        Mtx_InverseRT((s32)(gEftDust + 0x70), gBtlCamView);
        *(f32 *)(gEftDust + 0xA0) = 0.0f;
        *(f32 *)(gEftDust + 0xA8) = 0.0f;
        *(f32 *)(gEftDust + 0xA4) = 0.0f;
        EftWaterSplash_DrawList(*(s32 *)(gEftDust + 0x3C));
        EftWaterTrail_DrawList(*(s32 *)(gEftDust + 0x44));
        EftWaterRing_DrawList(*(s32 *)(gEftDust + 0x4C));
        EftWaterSpray_DrawList(*(s32 *)(gEftDust + 0x5C), (s32)D_002C3630);
        EftWaterDrop_DrawList(*(s32 *)(gEftDust + 0x54), (s32)D_002C3630);
        func_001404A0(*(s32 *)(gEftDust + 0x64));
        func_00128F08();
    }
}
