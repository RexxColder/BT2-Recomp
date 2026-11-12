#include "m2c_macros.h"

extern void Dma_AddData(s32 arg0, s32 arg1);
extern void Dma_AddFrame(s32 arg0, s32 arg1, s32 arg2);
extern s32 Dma_AddZbuf(s32 arg0, s32 arg1);
extern void GfxPost_ShiftHighWord(s32 arg0, s32 arg1, s32 arg2);
extern void func_00271370(void);
extern void func_00271A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5);
extern void func_002814D0(s32 arg0, s32 arg1, s64 arg2, s32 arg3);
extern u8 gGfx[] __attribute__((section(".data")));

void func_00285D98(u8 *arg0) {
    s32 flag;

    Dma_AddData((s32)(arg0 + 0x494), 0x10);
    func_00271370();
    Dma_AddZbuf(0xE0, 1);
    flag = *(s32 *)(gGfx + 0x234) & 1;
    GfxPost_ShiftHighWord(flag ? 0 : 0x70, 0x1C00, 0x380);
    Dma_AddFrame(0xE0, 8, 0xFFFFFF);
    func_00271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0xFE00 << 46);
    flag = *(s32 *)(gGfx + 0x234) & 1;
    func_002814D0(1, flag ? 0 : 0xE00, *(u16 *)(arg0 + 0x4B4), 0x44);
    flag = *(s32 *)(gGfx + 0x234) & 1;
    Dma_AddFrame(flag ? 0 : 0x70, 8, 0);
}
