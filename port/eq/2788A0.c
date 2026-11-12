#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1);
u8 *Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0);
void func_00271370(void);
s32 func_002784E0(u8 *arg0, s32 arg1, s32 arg2);

void func_002788A0(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *temp_v0;

    if (arg0 != NULL) {
        Dma_AddData(*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 8) * 16);
        func_00271370();
    }
    temp_v0 = Dma_BeginDirect();
    *(s64 *)(temp_v0 + 0x00) = ((s64)0x10000000 << 32) | 0x8003;
    *(s64 *)(temp_v0 + 0x08) = 0xE;
    *(s64 *)(temp_v0 + 0x10) = 0x44;
    *(s64 *)(temp_v0 + 0x18) = 0x42;
    *(s64 *)(temp_v0 + 0x20) = 0x60;
    *(s64 *)(temp_v0 + 0x28) = 0x14;
    *(s64 *)(temp_v0 + 0x30) = 0x30000;
    *(s64 *)(temp_v0 + 0x38) = 0x47;
    Dma_EndDirect(func_002784E0(temp_v0 + 0x40, arg2, arg1));
}
