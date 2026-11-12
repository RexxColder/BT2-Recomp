#include "common.h"

u8 *Dma_BeginDirect(s64 arg0);
void Dma_EndDirect(u8 *arg0, s32 arg1);

void func_00137838(s64 arg0) {
    u8 *temp_v0;
    u8 *var_a0;

    temp_v0 = Dma_BeginDirect(arg0);
    *(s64 *)(temp_v0 + 0) = ((s64)0x10000000 << 32) | 0x8001;
    *(s64 *)(temp_v0 + 8) = 0xE;
    var_a0 = temp_v0 + 0x10;
    if (arg0 == 0) {
        *(s64 *)(temp_v0 + 0x10) = 0x44;
        *(s64 *)(temp_v0 + 0x18) = 0x42;
        var_a0 += 0x10;
    } else if (arg0 == 1) {
        *(s64 *)(temp_v0 + 0x10) = 0x48;
        *(s64 *)(temp_v0 + 0x18) = 0x42;
        var_a0 += 0x10;
    } else if (arg0 == 2) {
        *(s64 *)(temp_v0 + 0x18) = 0x42;
        *(s64 *)(temp_v0 + 0x10) = 0x42;
        var_a0 += 0x10;
    }
    Dma_EndDirect(var_a0, 1);
}
