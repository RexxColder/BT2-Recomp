#include "m2c_macros.h"

extern void Dma_AddData(s32 arg0, s32 arg1);
extern void Dma_AddFrame(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00271370(void);
extern void func_0027BE68(void);
extern void func_002814D0(s32 arg0, s32 arg1, s64 arg2, s64 arg3);
extern s32 D_003B0A84 __attribute__((section(".data")));

void func_0027C320(u8 *arg0) {
    if (arg0[0x590] != 0) {
        Dma_AddData((s32)(arg0 + 0x494), 0x10);
        func_00271370();
        Dma_AddFrame((D_003B0A84 & 1) ? 0 : 0x70, 8, 0xFFFFFF);
        func_002814D0(0, 0x1C00, *(u16 *)(arg0 + 0x4B4), ((s64)0x80 << 32) | 0x48);
        func_0027BE68();
    }
}
