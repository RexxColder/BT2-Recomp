#include "common.h"

extern u8 *D_00387AD8;
extern u8 *gOtFirst;

void func_001EEFA0(s8 arg0, s64 *arg1) {
    u8 *temp_a2;
    u8 *v0;

    temp_a2 = D_00387AD8;
    D_00387AD8 += 0x30;
    if (temp_a2 != NULL) {
        *(s64 *)(temp_a2 + 0x28) = (s64)(arg0 + 6);
        *(s64 *)(temp_a2 + 0x0) = ((s64)0xA000 << 16) | 2;
        *(s64 *)(temp_a2 + 0x10) = ((s64)0x10000000 << 32) | 0x8001;
        *(s64 *)(temp_a2 + 0x18) = 0xE;
        *(s64 *)(temp_a2 + 0x20) = *arg1;
        v0 = *(u8 **)(gOtFirst + 4);
        *(u8 **)(v0 + 4) = temp_a2;
        *(u8 **)(gOtFirst + 4) = temp_a2;
    }
}
