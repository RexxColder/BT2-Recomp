#include "common.h"

s32 Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0, s32 arg1);
void EftStageScroll_PlaceTextures(s32 arg0, s32 arg1);
s32 EftStage_IsDrawOn(void);
void func_0012B9C0(void);
s32 func_001EC310(s32 arg0, s32 arg1);
void func_001EC3A0(s32 arg0, s32 arg1);
void func_001EC440(f32 farg0, s32 arg0);
void func_001EC488(s32 arg0, s32 arg1);
s32 func_00276D00(void);
s32 sceVu0UnitMatrix(s32 arg0);
void EftMesh_SetUvOfs(s32 arg0, f32 farg0, f32 farg1);
extern u8 *D_003876A0;
extern u8 *gEftStageScroll;
extern u8 *gBtlCamView;

void func_00130E30(void) {
    s32 sp[16];
    u8 *g;
    u8 *p;
    u8 *cam;

    g = gEftStageScroll;
    if (g != NULL && !(*(s64 *)(D_003876A0 + 0x4D8) & 0x2000)) {
        func_0012B9C0();
        if (g[0x2B0] != 0) {
            if (EftStage_IsDrawOn() != 0) {
                EftStageScroll_PlaceTextures(1, 0);
                p = (u8 *)Dma_BeginDirect();
                *(s64 *)(p + 0x00) = (s64)0x1000000000008003LL;
                *(s64 *)(p + 0x08) = 0xE;
                *(s64 *)(p + 0x10) = 0x44;
                *(s64 *)(p + 0x18) = 0x42;
                *(s64 *)(p + 0x20) = 0x50000;
                *(s64 *)(p + 0x28) = 0x47;
                *(s64 *)(p + 0x30) = 0;
                *(s64 *)(p + 0x38) = 8;
                Dma_EndDirect((s32)(p + 0x40), 0x50000);
                sceVu0UnitMatrix((s32)sp);
                if (func_00276D00() != 0) {
                    cam = gBtlCamView;
                    *(f32 *)&sp[12] = *(f32 *)(cam + 0x1F0);
                    sp[13] = 0;
                    *(f32 *)&sp[14] = *(f32 *)(cam + 0x1F8);
                } else {
                    sp[12] = 0;
                    sp[13] = 0;
                    sp[14] = 0;
                }
                func_001EC3A0((s32)(g + 0x210), 1);
                func_001EC440(*(f32 *)(g + 0x2A4), (s32)(g + 0x210));
                EftMesh_SetUvOfs((s32)(g + 0x210), *(f32 *)(g + 0x298), *(f32 *)(g + 0x29C));
                func_001EC310((s32)(g + 0x210), (s32)sp);
                func_001EC488((s32)(g + 0x210), 1);
            }
        }
    }
}
