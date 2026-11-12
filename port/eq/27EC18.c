#include "common.h"

void Dma_AddData(void *p, s32 n);
void Dma_AddFrame(s32 a, s32 b, s32 c);
s32 func_00271370(void);
void func_00271A00(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s64 a5);
void func_0027C4C8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_002814D0(s32 a0, s32 a1, s64 a2, s32 a3);
extern u8 gGfx[] __attribute__((section(".data")));

void func_0027EC18(u8 *arg0) {
    if (*(u8 *)(arg0 + 0x500) != 0) {
        Dma_AddData(arg0 + 0x4D4, 0x10);
        func_00271370();
        Dma_AddFrame((*(s32 *)(gGfx + 0x234) & 1) ? 0 : 0x70, 8, 0xFFFFFF);
        func_00271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0xFE00 << 46);
        Dma_AddFrame((*(s32 *)(gGfx + 0x234) & 1) ? 0 : 0x70, 8, 0xFFFFFF);
        func_002814D0(0, 0x1C00, *(u16 *)(arg0 + 0x4F4), 0x44);
        func_00271370();
        func_0027C4C8(0xA, *(s32 *)(arg0 + 0x504), *(u8 *)(arg0 + 0x502), *(s32 *)(arg0 + 0x508), 0, 0, 0);
    }
}
