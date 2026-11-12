#include "common.h"

extern u8 *D_00387AD8;
extern u8 *gOtFirst;

void func_001EF228(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 store20;
    s64 var_v0;
    u8 *temp_t0;

    temp_t0 = D_00387AD8;
    temp_a0 = arg0 != 0;
    D_00387AD8 = temp_t0 + 0x60;
    if (temp_t0 == 0) {
        return;
    }
    *(s64 *)(temp_t0 + 0x28) = (s64)(temp_a0 + 0x42);
    *(s64 *)(temp_t0 + 0x00) = (((s64)0xA000) << 16) | 5;
    *(s64 *)(temp_t0 + 0x10) = (((s64)0x10000000) << 32) | 0x8004;
    *(s64 *)(temp_t0 + 0x18) = 0xE;
    *(s64 *)(temp_t0 + 0x38) = 0x49;
    *(s64 *)(temp_t0 + 0x48) = 0x3B;
    *(s64 *)(temp_t0 + 0x58) = (s64)(temp_a0 + 0x4A);
    store20 = 1;
    if (arg1 == 1) {
        var_v0 = 0x48;
    } else if (arg1 == 0) {
        var_v0 = 0x44;
    } else if (arg1 == 2) {
        var_v0 = 0x42;
    } else {
        store20 = 0;
        var_v0 = 0;
    }
    if (store20) {
        *(s64 *)(temp_t0 + 0x20) = var_v0;
    }
    *(s64 *)(temp_t0 + 0x30) = 0;
    *(s64 *)(temp_t0 + 0x50) = 0;
    *(s64 *)(temp_t0 + 0x40) = (((s64)0x7F) << 32) | 0x807F;
    *(u8 **)(*(u8 **)(gOtFirst + 4) + 4) = temp_t0;
    *(u8 **)(gOtFirst + 4) = temp_t0;
}
