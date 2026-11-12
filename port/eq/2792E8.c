#include "common.h"

extern u8 *D_00387AD8;
extern u8 *gOt;

void *func_002792E8(s32 arg0) {
    u8 *temp_a2;

    temp_a2 = D_00387AD8;
    D_00387AD8 = temp_a2 + 0x30;
    *(s64 *)(temp_a2 + 0x0) = ((s64)0xA000 << 16) | 2;
    *(s64 *)(temp_a2 + 0x10) = ((s64)0x10000000 << 32) | 0x8001;
    *(s64 *)(temp_a2 + 0x18) = 0xE;
    *(s64 *)(temp_a2 + 0x28) = 0x42;
    *(s64 *)(temp_a2 + 0x20) = *(s64 *)(gOt + arg0 * 8 + 0x10);
    return temp_a2;
}
