#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1);
void *Dma_BeginDirect(void);
s32 Dma_EndDirect(s32 arg0);
void func_00271370(void);
s32 func_002786A0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg5);

s32 func_00278958(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg5) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    s32 r;

    if (arg0 != NULL) {
        Dma_AddData(*(s32 *)((u8 *)arg0 + 4), *(s32 *)((u8 *)arg0 + 8) << 4);
        func_00271370();
    }
    temp_v0 = (u8 *)Dma_BeginDirect();
    *(s64 *)(temp_v0 + 0x0) = (s64)0x1000000000008003ULL;
    *(s64 *)(temp_v0 + 0x8) = 0xE;
    temp_v0_2 = temp_v0 + 0x10;
    *(s64 *)(temp_v0 + 0x10) = 0x44;
    *(s64 *)(temp_v0_2 + 0x8) = 0x42;
    temp_v0_3 = temp_v0_2 + 0x10;
    *(s64 *)(temp_v0_3 + 0x8) = 0x14;
    *(s64 *)(temp_v0_2 + 0x10) = 0x60;
    temp_v0_4 = temp_v0_3 + 0x10;
    *(s64 *)(temp_v0_3 + 0x10) = 0x30000;
    *(s64 *)(temp_v0_4 + 0x8) = 0x47;
    r = func_002786A0(temp_v0_4 + 0x10, arg2, arg1, arg3, arg4, farg5);
    return Dma_EndDirect(r);
}
