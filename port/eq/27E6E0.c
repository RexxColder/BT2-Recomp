#include "common.h"

void Dma_AddData(u8 *p, s32 n);
void func_00271370(void);
void GfxPost_ClearWork(s32 a0, s32 a1);
void func_0027DE68(s32 a0, s32 a1, s32 a2, s64 a3, s32 t0, s32 t1);
void GfxPost_AddFrame16(s32 a0, s32 a1);
void GfxPost_AddScreenFrame(void);
void Dma_AddFrame(s32 a0, s32 a1, s32 a2);
void Dma_AddScissor(s32 a0, s32 a1, s32 a2, s32 a3);
void Dma_AddZbuf(s32 a0, s32 a1);
void func_00271A00(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s64 t1);
void Dma_AddColClamp(u64 a0);
void GfxPost_AddXyOffset(s32 a0, s32 a1);
void GfxPost_DrawTex16Texa(s32 a0, s64 a1, s32 a2);
void GfxPost_FillBlend(u64 a0, u64 a1);
extern void *D_003876A0;
extern u8 gGfx[] __attribute__((section(".data")));

void func_0027E6E0(u8 *arg0) {
    s64 temp_s2;
    u8 *G;

    temp_s2 = (s64)0x8000 << 46;
    Dma_AddData(arg0 + 0x4D4, 0x10);
    func_00271370();
    GfxPost_ClearWork(0x150, (s32)0xFF000000);
    func_0027DE68(0, 0x1C00, *(u16 *)(arg0 + 0x4F4), ((s64)0x80 << 32) | 0x44, 0, 0);
    GfxPost_AddFrame16(0x150, -0x100);
    func_0027DE68(0, 0x1C00, *(u16 *)(arg0 + 0x4F4), ((s64)0x80 << 32) | 0x62, 0, 8);
    GfxPost_AddFrame16(0x150, (s32)0xFFFF00FF);
    func_0027DE68(0, 0x1C00, *(u16 *)(arg0 + 0x4F4), ((s64)0x80 << 32) | 0x62, 0x10, 0);
    GfxPost_AddScreenFrame();
    Dma_AddFrame((*(s32 *)(gGfx + 0x234) & 1) ? 0 : 0x70, 8, 0xFFFFFF);
    Dma_AddScissor(0, 0x1FF, 0, 0x1BF);
    Dma_AddZbuf(0xE0, 1);
    func_00271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0xFE00 << 46);
    Dma_AddZbuf(0xE0, 1);
    Dma_AddFrame((*(s32 *)(gGfx + 0x234) & 1) ? 0 : 0x70, 8, 0);
    Dma_AddFrame((*(s32 *)(gGfx + 0x234) & 1) ? 0 : 0x70, 8, 0xFFFFFF);
    Dma_AddColClamp(1);
    G = (u8 *)D_003876A0;
    if ((*(s64 *)(G + 0x4D8) & temp_s2) == 0) {
        GfxPost_AddXyOffset(0x7000, 0x7210);
        GfxPost_DrawTex16Texa(0x2A00, ((s64)0x80 << 32) | 0x64, 0x30);
        GfxPost_AddXyOffset(0x7000, 0x71F0);
        GfxPost_DrawTex16Texa(0x2A00, ((s64)0x80 << 32) | 0x64, 0x30);
    }
    GfxPost_AddXyOffset(0x7000, 0x7200);
    GfxPost_DrawTex16Texa(0x2A00, 0x44, 0x80);
    Dma_AddFrame((*(s32 *)(gGfx + 0x234) & 1) ? 0 : 0x70, 8, 0);
    if ((*(s64 *)(G + 0x4D8) & temp_s2) != 0) {
        GfxPost_FillBlend(0x52, ((((s64)0x3F800000 << 16) | 0x8080) << 16) | 0x8080);
        return;
    }
    GfxPost_FillBlend(0x52, ((((s64)0x3F800000 << 16) | 0x8050) << 16) | 0x5050);
}
