#include "common.h"

extern s32 D_00387AD8;
extern s32 D_00387AE4;

void func_0012EB10(s64 arg0) {
    s32 temp_v1;

    temp_v1 = D_00387AD8;
    D_00387AD8 = temp_v1 + 0x30;
    *(s64 *)(temp_v1 + 0x00) = ((s64)0xA000 << 16) | 2;
    *(s64 *)(temp_v1 + 0x10) = ((s64)0x10000000 << 32) | 0x8001;
    *(s64 *)(temp_v1 + 0x18) = 0xE;
    *(s64 *)(temp_v1 + 0x20) = arg0;
    *(s64 *)(temp_v1 + 0x28) = 0x42;
    *(s32 *)(*(s32 *)(D_00387AE4 + 4) + 4) = temp_v1;
    *(s32 *)(D_00387AE4 + 4) = temp_v1;
}
