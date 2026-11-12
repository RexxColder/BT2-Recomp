#include "common.h"

s32 func_002B6040(u8 *arg0) {
    s32 temp_a2;
    s32 q;
    s32 r;
    u8 *temp_a1;

    temp_a2 = *(s32 *)(arg0 + 0xB8);
    q = (temp_a2 < 0 ? temp_a2 + 7 : temp_a2) >> 3;
    r = temp_a2 - q * 8;
    temp_a1 = arg0 + r * 0x14 + 0xC0;
    if (*(s32 *)temp_a1 == 1) {
        return *(s32 *)(temp_a1 + 0xC);
    }
    return 0;
}
