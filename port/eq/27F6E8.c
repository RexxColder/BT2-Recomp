#include "m2c_macros.h"

extern void Dma_AddData(s32 arg0, s32 arg1);
extern void Dma_AddFrame(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00271370(void);
extern void func_0027C4C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_0027F538(s32 arg0);
extern void func_002814D0(s32 arg0, s32 arg1, s64 arg2, s64 arg3);
extern s32 D_00387AF0;
extern s32 D_00387AF4;
extern u8 gGfx[] __attribute__((section(".data")));

void func_0027F6E8(u8 *arg0) {
    s32 flag;

    func_0027F538((s32)arg0);
    Dma_AddData((s32)(*(u8 **)(arg0 + 0x9C0) + 0x494), 0x10);
    func_00271370();
    flag = *(s32 *)(gGfx + 0x234) & 1;
    Dma_AddFrame(flag ? 0 : 0x70, 8, 0xFFFFFF);
    func_002814D0(0, 0x1C00, *(u16 *)(*(u8 **)(arg0 + 0x9C0) + 0x4B4), 0x44);
    flag = *(s32 *)(gGfx + 0x234) & 1;
    Dma_AddFrame(flag ? 0 : 0x70, 8, 0);
    func_0027C4C8(0xA, D_00387AF0, 1, D_00387AF4, 1, 0, 0);
}
