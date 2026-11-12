#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE4;

void func_0012EAA8(void) {
    u8 *temp_v1;
    u8 *blk;

    temp_v1 = D_00387AD8;
    D_00387AD8 = temp_v1 + 0x40;
    *(s64 *)(temp_v1 + 0x20) = 0x50000;
    *(s64 *)(temp_v1 + 0x00) = ((s64)0xA000 << 16) | 3;
    *(s64 *)(temp_v1 + 0x10) = ((s64)0x10000000 << 32) | 0x8002;
    *(s64 *)(temp_v1 + 0x18) = 0xE;
    *(s64 *)(temp_v1 + 0x28) = 0x47;
    *(s64 *)(temp_v1 + 0x30) = 0x60;
    *(s64 *)(temp_v1 + 0x38) = 0x14;
    blk = *(u8 **)(D_00387AE4 + 4);
    *(u8 **)(blk + 4) = temp_v1;
    *(u8 **)(D_00387AE4 + 4) = temp_v1;
}
