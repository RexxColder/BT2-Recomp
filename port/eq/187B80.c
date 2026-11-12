#include "common.h"

extern s32 D_003877B0;

void func_00187B80(s32 arg0, s32 arg1) {
    s64 sp0;
    s64 sp8;
    s64 temp_a1;
    s32 temp_a0;

    temp_a1 = *(s64 *)(arg1 + 0);
    sp8 = *(s64 *)(arg1 + 8);
    sp0 = temp_a1;
    if ((D_003877B0 != 0) && (arg0 != 0)) {
        temp_a0 = *(s32 *)(arg0 + 0x38);
        if ((temp_a0 != 0) && ((*(s32 *)(temp_a0 + 0x19C) & 2) != 0)) {
            *(s64 *)(temp_a0 + 0x70) = temp_a1;
            *(s64 *)(temp_a0 + 0x78) = sp8;
        }
    }
}
